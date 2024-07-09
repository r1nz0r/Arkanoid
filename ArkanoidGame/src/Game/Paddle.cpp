#include "Game/Paddle.h"
#include "Game/GameSettings.h"
#include "Framework/MathUtils.h"
#include "Framework/Core.h"

namespace Arkanoid
{
	Paddle::Paddle(World* owner)
		: Actor(owner)
		, m_direction(EMoveDirection::None)
		, m_velocity()
		, m_speed(PADDLE_SPEED)
		, m_moveInput()
		, m_collider({ 0.f, 0.f }, {PADDLE_WIDTH, PADDLE_HEIGHT})
	{
		m_shape.reset(new sf::RectangleShape({PADDLE_WIDTH, PADDLE_HEIGHT }));
		CenterPivot();
	}

	void Paddle::Tick(float deltaTime)
	{
		HandleInput();
		ConsumeInput(deltaTime);
		AddPositionOffset(m_velocity * deltaTime);
		ClampPosition();
	}

	void Paddle::BeginPlay()
	{
		m_shape->setFillColor(sf::Color::Cyan);
		SetPosition({ 400.f, 580.f });
	}

	void Paddle::SetVelocity(const sf::Vector2f& velocity)
	{
		m_velocity = velocity;
	}

	void Paddle::SetPosition(const sf::Vector2f& newPosition)
	{
		Actor::SetPosition(newPosition);
		m_collider.SetPosition(GetPosition() - sf::Vector2f(PADDLE_WIDTH / 2, PADDLE_HEIGHT / 2));
		LOG("Position paddle left corner: %f, Position collider left corner: %f", GetPosition().x, m_collider.GetPosition().x);
	}

	void Paddle::AddPositionOffset(const sf::Vector2f & offset)
	{
		Actor::AddPositionOffset(offset);
		m_collider.SetPosition(m_collider.GetPosition() + offset);
	}

	void Paddle::HandleInput()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			m_moveInput.x = -1.0f;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			m_moveInput.x = 1.0f;

		Math::GetNormalizedVector(m_moveInput);
	}



	void Paddle::ConsumeInput(float deltaTime)
	{
		SetVelocity(m_moveInput * m_speed);
		m_moveInput.x = m_moveInput.y = 0;
	}

	void Paddle::ClampPosition()
	{
		if (!m_owner)
			return;	

		auto position = GetPosition();
		auto size = GetGlobalBounds();

		if (position.x - size.width / 2 <= 0.f)
			position.x = size.width / 2;
		else if (position.x + size.width / 2 >= SCREEN_WIDTH)
			position.x = SCREEN_WIDTH - size.width / 2;

		if (position.y - size.height / 2 <= 0.f)
			position.y = size.height / 2;
		else if (position.y + size.height / 2 >= SCREEN_HEIGHT)
			position.y = SCREEN_HEIGHT - size.height / 2;

		SetPosition(position);
	}
}