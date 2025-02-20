#pragma once



template<typename T>
class Singleton
{
	public:
		Singleton() = default;
		~Singleton() = default;

		static const std::shared_ptr<T> Get()
		{
			static std::shared_ptr<T> singleton = std::make_shared<T>();

			return singleton;
		}
};