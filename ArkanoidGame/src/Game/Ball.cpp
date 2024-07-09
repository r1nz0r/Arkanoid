#include "Game/Ball.h"
#include "Game/GameSettings.h"
#include "Framework/World.h"
#include "Game/Paddle.h"
#include "Framework/MathUtils.h"

namespace Arkanoid
{
	Ball::Ball(World* owner)
		: Actor(owner)
		, m_speed(BALL_INITIAL_SPEED)
		, m_velocity(0.f, 0.f)
		, m_bounceDirection(0)
		, m_isAttached(true)
		, m_collider({ 0.f, 0.f }, BALL_SIZE)
	{
		m_shape.reset(new sf::CircleShape(BALL_SIZE, 30u));
		m_shape->setFillColor(sf::Color::Green);
		CenterPivot();
	}

	void Ball::Tick(float deltaTime)
	{
		if (IsAttachedToPaddle())
		{
			if (auto paddle = m_owner->GetPaddle().lock())
				SetPosition(paddle->GetPosition() - sf::Vector2f(0.f, PADDLE_HEIGHT / 2 + BALL_SIZE));

			return;
		}

		DoCollisionTests();
		UpdateBounceDirection();

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

	void Ball::OnPaddleCollision(const Rectangle& other)
	{
		const float bounceAngle = GetPaddleBounceAngle(other);
		const float normalizedHitPosition = GetPaddleHitNormalizedPoint(other);
		m_speed = BALL_INITIAL_SPEED + std::abs(normalizedHitPosition) * BALL_ANGLE_ACCELERATION;
		m_velocity.x = -std::sin(bounceAngle);
		m_velocity.y = std::cos(bounceAngle);
		m_velocity = Math::GetNormalizedVector(m_velocity);

		SetBounceDirection(BounceDirectionBitMask::Up);
	}

	void Ball::DoCollisionTests()
	{
		std::weak_ptr<Paddle> paddle = m_owner->GetPaddle();

		if (paddle.expired())
			return;

		auto paddleCollider = paddle.lock()->GetCollider();

		if (Collider::CheckCollision(m_collider, paddleCollider))
			OnPaddleCollision(paddleCollider);
		else
		{
			if (Collider::CheckVerticalBoundsCollision(m_collider))
			{
				OnVerticalBoundsCollision();
			}
			else if (Collider::CheckHorizontalBoundsCollision(m_collider))
			{
				OnHorizontalBoundsCollision();
			}
		}
	}

	void Ball::Detach()
	{
		if (!m_isAttached)
			return;

		m_isAttached = false;
		SetVelocity({ 0.f, -1.0f });
	}

	bool Ball::CheckBounceDirection(BounceDirectionBitMask flags)
	{
		return m_bounceDirection & static_cast<uint8_t>(flags);
	}

	void Ball::SetBounceDirection(BounceDirectionBitMask flag)
	{
		m_bounceDirection |= static_cast<uint8_t>(flag);
	}

	void Ball::BeginPlay()
	{
		SetPosition({ 400.f, 570.f });
	}

	void Ball::SetVelocity(const sf::Vector2f& velocity)
	{
		m_velocity = velocity;
	}

	void Ball::SetPosition(const sf::Vector2f& newPosition)
	{
		Actor::SetPosition(newPosition);
		m_collider.SetPosition(newPosition);
	}

	void Ball::AddPositionOffset(const sf::Vector2f& offset)
	{
		Actor::AddPositionOffset(offset);
		m_collider.SetPosition(m_collider.GetPosition() + offset);
	}

	float Ball::GetPaddleBounceAngle(const Rectangle& paddle) const
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
		if (m_collider.GetPosition().y > SCREEN_HEIGHT / 2.f)
			SetBounceDirection(BounceDirectionBitMask::Down);
		else
			SetBounceDirection(BounceDirectionBitMask::Up);
	}

	void Ball::OnHorizontalBoundsCollision()
	{
		if (m_collider.GetPosition().x > SCREEN_HEIGHT / 2.f)
			SetBounceDirection(BounceDirectionBitMask::Left);
		else
			SetBounceDirection(BounceDirectionBitMask::Right);	
	}
}