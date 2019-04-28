//Library Includes
#include <iostream>
#include <thread>
#include <functional>

//Local Includes
#include "WorkQueue.h"
#include "Task.h"

//This Include
#include "ThreadPool.h"

//Static Variables
ThreadPool* ThreadPool::s_pThreadPool = nullptr;

ThreadPool::ThreadPool()
{
	m_iNumberOfThreads = std::thread::hardware_concurrency();
}


ThreadPool::ThreadPool(unsigned int _size)
{
	//Create a pool of threads equal to specified size
	m_iNumberOfThreads = _size;
}

ThreadPool::~ThreadPool()
{
	m_bStop = true;
	for (unsigned int i = 0; i < m_iNumberOfThreads; i++)
	{
		m_workerThreads[i].join();
	}

	delete m_pWorkQueue;
	m_pWorkQueue = 0;
}

ThreadPool& ThreadPool::GetInstance()
{
	if (s_pThreadPool == nullptr)
	{
		s_pThreadPool = new ThreadPool();
	}
	return (*s_pThreadPool);
}

void ThreadPool::DestroyInstance()
{
	delete s_pThreadPool;
	s_pThreadPool = 0;
}

void ThreadPool::Initialize()
{
	//Create a new Work Queue
	m_pWorkQueue = new CWorkQueue<CTask>();
}

void ThreadPool::Start()
{
	for (unsigned int i = 0; i < m_iNumberOfThreads; i++)
	{
		m_workerThreads.push_back(std::thread(&ThreadPool::DoWork, this));
	}
	m_bStop = false;
}

void ThreadPool::Submit(CTask _fItem)
{
	m_pWorkQueue->push(_fItem);
}

void ThreadPool::Stop()
{
	m_bStop = true;

	// TEST
	for (unsigned int i = 0; i < m_iNumberOfThreads; i++)
	{
		m_workerThreads[i].join();
	}
	m_workerThreads.clear();
	this->m_pWorkQueue->clear();
	this->m_aiItemsProcessed = 0;
}


void ThreadPool::DoWork()
{
	//Entry point of  a thread.
	std::cout << " MAGIC INFO: " << std::this_thread::get_id(); //Without this line the whole program hangs
	while (!m_bStop)
	{
		CTask WorkItem;
		//If there is an item in the queue to be processed; just take it off the q and process it
		if (m_pWorkQueue->blocking_pop(WorkItem,500))
		{
			WorkItem();
			m_aiItemsProcessed++;
		}
		//Else just continue back to the beginning of the while loop.
		else
		{
			continue;
		}
	}
}

std::atomic_int& ThreadPool::getItemsProcessed()
{
	return m_aiItemsProcessed;
}

