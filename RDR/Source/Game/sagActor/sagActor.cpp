#include <pch.h>



namespace rage
{
	void hlthHealthComponent::SetMaxHitPoints(float _MaxHitPoints)
	{
		m_MaxHitPoints = _MaxHitPoints;
	}



	Vector3 mvrMoverComponent::GetPosition() const
	{
		return m_Transform.Position;
	}



	Vector3 mvrMoverComponent::GetRotation() const
	{
		// Get the pitch, yaw and roll from the matrix (forward, up & right vectors)
		float pitch = -asin(m_Transform.Forward.Z);
		float yaw = atan2(m_Transform.Forward.Y, m_Transform.Forward.X);
		float roll = atan2(m_Transform.Up.Z, m_Transform.Right.Z);

		// Convert from radians to degrees
		pitch *= Math<float>::RadToDeg;
		yaw *= Math<float>::RadToDeg;
		roll *= Math<float>::RadToDeg;

		// Fix when we're in the pitch "flipping" side, so we get proper ±0° to ±180° range instead
		// This is a fix bcs 'asin()' function is limited in a range of ±0° to ±90°
		if (m_Transform.Forward.X < 0.0f)
			pitch = 180.0f - pitch;

		// Normalize the angles
		pitch = Math<float>::NormalizeAngle(pitch);
		yaw = Math<float>::NormalizeAngle(yaw);
		roll = Math<float>::NormalizeAngle(roll);

		return Vector3(yaw, pitch, roll);
	}



	bool sagActor::IsAlive() const
	{
		return m_HealthComponent && m_HealthComponent->m_CurrentHealth > 0.0f;
	}



	bool sagActor::IsDrunk() const
	{
		return m_HealthComponent && m_HealthComponent->m_IsDrunk;
	}
}