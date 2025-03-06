#include <pch.h>



void FibersPool::DoRun(RunFilter _RunFilter)
{
	for (const auto& atomicFiber : m_Fibers[_RunFilter])
	{
		std::shared_ptr<IFiber> fiber = atomicFiber.load();

		if (fiber)
			fiber->Tick();
	}
}



void FibersPool::DoGarbageCollection()
{
	for (size_t i = 0; i < RUN_FILTER_COUNT; ++i)
	{
		for (size_t j = 0; j < POOL_SIZE; ++j)
		{
			auto& atomicFiber = m_Fibers[i][j];

			std::shared_ptr<IFiber> fiber = atomicFiber.load();

			if (fiber && fiber->IsDirty())
			{
				if (atomicFiber.compare_exchange_weak(fiber, nullptr))
				{
					const std::string name = fiber->GetName();

					LOG_DEV_INFO("Garbage collected fiber '%s' (%d%zu) (Remaining: %llu)", name.c_str(), i, j, Count());
				}
			}
		}
	}
}



void FibersPool::Add(RunFilter _RunFilter, const std::shared_ptr<IFiber>& _Fiber)
{
	const std::string name = _Fiber->GetName();

	for (size_t i = 0; i < POOL_SIZE; ++i)
	{
		std::shared_ptr<IFiber> fiber = nullptr;

		if (m_Fibers[_RunFilter][i].compare_exchange_weak(fiber, _Fiber))
		{
			LOG_DEV_INFO("Registered fiber '%s' (%u%zu)", name.c_str(), _RunFilter, i);

			m_LastUniqueId++;

			return;
		}
	}

	LOG_DEV_ERROR("Failed to create fiber '%s', fibers pool is full !", name.c_str());
}



void FibersPool::Remove(RunFilter _RunFilter, size_t _Index)
{
	if (_RunFilter >= RUN_FILTER_COUNT)
	{
		LOG_DEV_ERROR("Failed to remove fiber '%zu', invalid run filter", _Index);

		return;
	}

	if (_Index >= POOL_SIZE)
	{
		LOG_DEV_ERROR("Failed to remove fiber '%zu', invalid index", _Index);

		return;
	}

	std::shared_ptr<IFiber> fiber = m_Fibers[_RunFilter][_Index].load();

	if (fiber && m_Fibers[_RunFilter][_Index].compare_exchange_weak(fiber, nullptr))
	{
		const std::string name = fiber->GetName();

		LOG_DEV_INFO("Removed fiber '%s' (%u%zu)", name.c_str(), _RunFilter, _Index);

		return;
	}

	LOG_DEV_ERROR("Failed to remove fiber '%zu', not found", _Index);
}




void FibersPool::Clear()
{
	for (auto& atomicFibers : m_Fibers)
	{
		for (auto& atomicFiber : atomicFibers)
		{
			std::shared_ptr<IFiber> fiber = atomicFiber.load();

			atomicFiber.compare_exchange_weak(fiber, nullptr);
		}
	}

	LOG_DEV_INFO("Removed all fibers");
}



size_t FibersPool::Count() const
{
	size_t count = 0;

	for (const auto& atomicFibers : m_Fibers)
	{
		for (const auto& atomicFiber : atomicFibers)
		{
			if (atomicFiber.load())
				++count;
		}
	}

	return count;
}