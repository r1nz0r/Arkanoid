#include "Game/Ball.h"
#include "Game/GameSettings.h"
#include "Game/GameLevel.h"
#include "Game/Paddle.h"
#include "Framework/MathUtils.h"
#include "Framework/Collider.h"
#include "Framework/PhysicsEngine.h"

namespace Arkanoid
{
	Ball::Ball(World* owner)
		: PhysicsActor(owner, std::unique_ptr<Circle>(new Circle({ 0.f, 0.f }, BALL_SIZE)))
		, m_speed(BALL_INITIAL_SPEED)
		, m_velocity(0.f, 0.f)
		, m_bounceDirection((uint8_t)BounceDirectionBitMask::None)
		, m_isAttached(true)
	{
		m_shape.reset(new sf::CircleShape(BALL_SIZE, 30u));
		m_shape->setFillColor(sf::Color::Green);
		CenterPivot();
	}

	void Ball::Tick(float deltaTime)
	{
		if (IsAttachedToPaddle())
		{
			if (auto paddle = static_cast<GameLevel*>(m_owner)->GetPaddle().lock())
				SetPosition(paddle->GetPosition() - sf::Vector2f(0.f, PADDLE_HEIGHT));

			return;
		}

		auto moveDistance = m_velocity * m_speed * deltaTime;
		AddPositionOffset(moveDistance);
	}

	void Ball::UpdateBounceDirection()
	{
		if (CheckBounceDirection(BounceDirectionBitMask::Horizontal))
			m_velocity.x = -m_velocity.x;
		if (CheckBounceDirection(BounceDirectionBitMask::Vertical))
			m_velocity.y = -m_velocity.y;

		m_bounceDirection &= (int)BounceDirectionBitMask::None;
	}

	void Ball::OnCollisionEnter(const ICollidable& other)
	{
		std::weak_ptr<Paddle> paddle = static_cast<GameLevel*>(m_owner)->GetPaddle();

		if (!paddle.expired() && other.GetOwner()->GetId() == paddle.lock()->GetId())
			OnPaddleCollision(static_cast<Rectangle&>(paddle.lock()->GetCollider()));
		else if (other.GetOwner()->GetId() == GetId())
		{
			if (PhysicsWorld::Instance().GetBoundsCollisionType() == BoundsCollider::ECollisionType::Horizontal)
				OnHorizontalBoundsCollision();
			else
				OnVerticalBoundsCollision();
		}

		UpdateBounceDirection();
	}

	void Ball::OnPaddleCollision(const Rectangle& other)
	{
		const float bounceAngle = GetBounceAngleFromPaddle(other);
		const float normalizedHitPosition = GetPaddleHitNormalizedPoint(other);
		m_speed = BALL_INITIAL_SPEED + std::abs(normalizedHitPosition) * BALL_ANGLE_ACCELERATION;
		m_velocity.x = -std::sin(bounceAngle);
		m_velocity.y = std::cos(bounceAngle);
		m_velocity = Math::GetNormalizedVector(m_velocity);

		SetBounceDirection(BounceDirectionBitMask::Up);
	}

	void Ball::Detach()
	{
		if (!m_isAttached)
			return;

		m_isAttached = false;
		SetVelocity({ 0.5f, -1.0f });
	}

	void Ball::SetPosition(const sf::Vector2f& newPosition)
	{
		PhysicsActor::SetPosition(newPosition);

		if (!m_collider)
			return;

		auto shapeBounds = m_shape->getLocalBounds();
		m_collider->SetPosition(GetPosition());
	}

	bool Ball::CheckBounceDirection(BounceDirectionBitMask flags) const
	{
		return m_bounceDirection & static_cast<uint8_t>(flags);
	}

	void Ball::SetBounceDirection(BounceDirectionBitMask flag)
	{
		m_bounceDirection |= static_cast<uint8_t>(flag);
	}

	void Ball::BeginPlay()
	{
		PhysicsActor::BeginPlay();
		SetPosition({ 400.f, 550.f });
	}

	void Ball::SetVelocity(const sf::Vector2f& velocity)
	{
		m_velocity = velocity;
	}

	float Ball::GetBounceAngleFromPaddle(const Rectangle& paddle) const
	{
		const float normalizedHitPositionX = GetPaddleHitNormalizedPoint(paddle);
		return Math::GetRadiansFromDegrees(normalizedHitPositionX * BOUNCE_ANGLE_MAX);
	}

	float Ball::GetPaddleHitNormalizedPoint(const Rectangle& paddle) const
	{
		const float relativeHitPositionX = (paddle.GetPosition().x + PADDLE_WIDTH / 2.f) - GetPosition().x;
		return relativeHitPositionX / (PADDLE_WIDTH / 2.f);
	}

	void Ball::OnVerticalBoundsCollision()
	{
		if (m_collider->GetPosition().y > SCREEN_HEIGHT / 2.f)
			SetBounceDirection(BounceDirectionBitMask::Down);
		else
			SetBounceDirection(BounceDirectionBitMask::Up);
	}

	void Ball::OnHorizontalBoundsCollision()
	{
		if (m_collider->GetPosition().x > SCREEN_HEIGHT / 2.f)
			SetBounceDirection(BounceDirectionBitMask::Left);
		else
			SetBounceDirection(BounceDirectionBitMask::Right);
	}
}