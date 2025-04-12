#include <pch.h>



namespace rage
{
	void mvrMoverComponent::EnableMoverCollision(bool _Enable)
	{
		if (!SigsDatabase::s_mvrMoverComponent__EnableMoverCollision)
			return;

		return SigsDatabase::s_mvrMoverComponent__EnableMoverCollision(this, _Enable);
	}



	Vector3 mvrMoverComponent::GetPosition() const
	{
		return m_Transform.Position;
	}



	Vector3 mvrMoverComponent::GetRotation() const
	{
		// The yaw is correct, but idk about the calculation for pitch & roll
		// I'm not an expert regarding angles/trigo stuff tbh, so this need to be verified
		float pitch = atan2(m_Transform.Forward.Y, m_Transform.Forward.X) * Math<float>::RadToDeg;
		float yaw = atan2(m_Transform.Right.X, m_Transform.Right.Z) * Math<float>::RadToDeg;
		float roll = atan2(m_Transform.Up.Z, m_Transform.Right.Z) * Math<float>::RadToDeg;

		return Vector3(pitch, yaw, roll);
	}
}