#pragma once



class Features : public Fiber
{
	public:
		Features();

		// static inline bool s_EnablePlayerCollision = true;

	private:
		virtual void Update();
};