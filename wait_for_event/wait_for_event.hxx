#pragma once

#include <mutex>
#include <atomic>
#include <chrono>
#include <iostream>
#include <optional>
#include <condition_variable>

namespace wfe
{
	enum class WaitForEventStatus : std::uint8_t
	{
		Error = 0,
		Timeout,
		NoTimeout,
		NoError  //Required for just wait
	};

	class WaitForEvent
	{
	private:
		std::mutex              mutex;
		std::condition_variable condition_variable;
		std::atomic_int32_t		thread_count{ 0 }; //Blocking and Non-Blocking thread
	public:

		void notify_one(void) noexcept
		{
			this->condition_variable.notify_one();
		}

		void notify_all(void) noexcept
		{
			this->condition_variable.notify_all();
		}

		void wait(void)
		{
			std::unique_lock<std::mutex> lock(this->mutex);
			this->condition_variable.wait(lock);
		}

		template <class Rep, class Period>
		WaitForEventStatus wait_for(const std::chrono::duration<Rep, Period>& wait_time)
		{
			try
			{
				std::unique_lock<std::mutex> lock(this->mutex);
				auto return_status = this->condition_variable.wait_for(lock, wait_time);
				if (return_status == std::cv_status::no_timeout)
				{
					return WaitForEventStatus::NoTimeout;
				}
				else
				{
					return WaitForEventStatus::Timeout;
				}
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what() << '\n';
				return WaitForEventStatus::Error;
			}
		}

		template <class Clock, class Duration>
		WaitForEventStatus wait_until(const std::chrono::time_point<Clock, Duration>& abs_time)
		{
			try
			{
				std::unique_lock<std::mutex> lock(this->mutex);
				auto return_status = this->condition_variable.wait_until(lock, abs_time);
				if (return_status == std::cv_status::no_timeout)
				{
					return WaitForEventStatus::NoTimeout;
				}
				else
				{
					return WaitForEventStatus::Timeout;
				}
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what() << '\n';
				return WaitForEventStatus::Error;
			}
		}

		WaitForEvent() = default;
		~WaitForEvent() = default;
	};

}
