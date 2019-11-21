#include "Cluster.h"
#include "Cluster.cpp"
#include <gtest.h>

TEST(Cluster, can_create_cluster)
{
	ASSERT_NO_THROW(Cluster st());
}
TEST(Cluster, can_valid_task)
{
	Cluster st;

	Task task;
	task.processors = 1;
	
	task.cores.push_back(1);

	task.priority = rand() % 5 + 1;
	task.tacts = rand() % 5 + 1;

	bool k = st.validTask(task);

	EXPECT_EQ(k, 1);
}
TEST(Cluster, cluster_can_invalid_task)
{
	Cluster st;
	Task task;
	task.processors = 100;

	task.cores.push_back(1);

	task.priority = rand() % 5 + 1;
	task.tacts = rand() % 5 + 1;

	EXPECT_EQ(st.validTask(task), 0);
}

TEST(Cluster, can_set_task)
{
	Cluster st;

	Task task;
	task.processors = 1;

	task.cores.push_back(1);

	task.priority = rand() % 5 + 1;
	task.tacts = rand() % 5 + 1;

	bool k = st.setTaskOnCluster(task);

	EXPECT_EQ(k, 1);
}


