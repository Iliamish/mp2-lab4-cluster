#include "TQueue.h"
#include <gtest.h>

TEST(TQueue, can_create_stack)
{
	ASSERT_NO_THROW(TQueue<int> st());
}
TEST(TQueue, can_check_empty)
{
	TQueue<int> st;
	EXPECT_EQ(1, st.empty());
}
TEST(TQueue, throw_when_try_pop_from_empty_stack)
{
	TQueue<int>st;
	ASSERT_ANY_THROW(st.pop());
}
TEST(TQueue, can_push)
{
	TQueue<int>st;
	st.push(0);
	st.push(0);
	ASSERT_NO_THROW(st.push(0));
}
TEST(TQueue, can_pop_to_stack)
{
	TQueue<int>st;
	st.push(1);
	ASSERT_NO_THROW(st.pop());
}
TEST(TQueue, can_push_tasks)
{
	TQueue<Task>st;
	for (int i = 0; i < 10; i++) {
		Task task;
		task.processors = rand() % MaxProcessors + 1;
		for (int i = 0; i < task.processors; ++i) {
			task.cores.push_back(rand() % MaxCores + 1);
		}
		task.priority = rand() % 5 + 1;
		task.tacts = rand() % 5 + 1;
		st.push(task);
	}
	Task task;
	task.processors = rand() % MaxProcessors + 1;
	for (int i = 0; i < task.processors; ++i) {
		task.cores.push_back(rand() % MaxCores + 1);
	}
	task.priority = rand() % 5 + 1;
	task.tacts = rand() % 5 + 1;
	ASSERT_NO_THROW(st.push(task));

}
TEST(TQueue, can_push_task_with_priority)
{
	TQueue<Task>st;
	Task task1;
	task1.processors = rand() % MaxProcessors + 1;
	for (int i = 0; i < task1.processors; ++i) {
		task1.cores.push_back(rand() % MaxCores + 1);
	}
	task1.priority = 1;
	task1.tacts = rand() % 5 + 1;
	st.push(task1);
	Task task2;
	task2.processors = rand() % MaxProcessors + 1;
	for (int i = 0; i < task2.processors; ++i) {
		task2.cores.push_back(rand() % MaxCores + 1);
	}
	task2.priority = 10;
	task2.tacts = rand() % 5 + 1;
	st.push(task2);
	EXPECT_EQ(st.front().priority, 10);
}

TEST(TQueue, can_inc_task_priority)
{
	TQueue<Task>st;
	Task task1;
	task1.processors = rand() % MaxProcessors + 1;
	for (int i = 0; i < task1.processors; ++i) {
		task1.cores.push_back(rand() % MaxCores + 1);
	}
	task1.priority = 1;
	task1.tacts = rand() % 5 + 1;
	st.push(task1);
	st.incPriority();
	EXPECT_EQ(st.front().priority, 2);
}