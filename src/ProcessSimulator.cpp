/** @file ProcessSimulator.cpp
 * @brief ProcessSimulator implementations
 *
 * @author Student Name
 * @note   cwid: 123456
 * @date   Fall 2019
 * @note   ide:  g++ 8.2.0 / GNU Make 4.2.1
 *
 * Implementation file for our Process Simulator class and
 * supporting functions.
 */
#include "ProcessSimulator.hpp"

using namespace std;

/**
 * @brief ProcessSimulator default constructor
 *
 * Default constructor for the Process simulator.
 * This constructor will initialize the system state to
 * have no processes, and start with a system time of 1
 * and next process id of 1.
 *
 * @param timeSliceQuantum The basic system time slice quantum
 *   given to a scheduled process.  This represents a const value
 *   used by our simulation as all processes when scheduled will
 *   only be given this basic time slice quantum to execute.
 */
ProcessSimulator::ProcessSimulator(Pid timeSliceQuantum)
{
  // task 1, need to initialize the timeSliceQuantum,
  // and also need to initialize all other member variables
  // here like systemTime, nextProcessId, etc.
  this->timeSliceQuantum = timeSliceQuantum;
  this->nextProcessId = 1;
  this->systemTime = 1;
  this->numFinishedProcesses = 0;
  this->cpu = IDLE;

  // add in a special IDLE dummy process to process control block
  processControlBlock[0] = Process();
}

/**
 * @brief ProcessSimulator destructor
 *
 * Destructor for the Process simulator.  We simply reuse
 * the reset method because part of a reset is freeing
 * any dynamically allocated resources.
 */
ProcessSimulator::~ProcessSimulator()
{
  this->reset();
}

/**
 * @brief ProcessSimulator reset
 *
 * Reset the Processs simulator back to clean state.
 * The actual work of deallocation and initialization
 * is done here so we can call on destruction or reload
 * of a program.
 */
void ProcessSimulator::reset() {}

/**
 * @brief system time slice quantum
 *
 * Accessor method to access the global system time slice quantum setting.
 * The time slice quantum is an important setting.  It determins how long
 * scheduled processes run on the simulated cpu until they need to be timed
 * out and returned back to the ready queue.
 *
 * @returns Time returns the setting of the system time slice scheduling
 *   quantum parameter.
 */// task 1 this getter should return the member variable

Pid ProcessSimulator::getTimeSliceQuantum() const
{
  // task 1 this getter should return the member variable
  return timeSliceQuantum;
}

/**
 * @brief next process id
 *
 * Accessor method to return the next process id that will be assigned
 * to the next new process.
 *
 * @returns Pid Returns the integer id of the next process id to be assigned.
 */
Pid ProcessSimulator::getNextProcessId() const
{
  // task 1 this getter should return the member variable
  return nextProcessId;
}

/**
 * @brief current system time
 *
 * Accessor method to return the current system time setting.
 *
 * @returns Pid Returns the integer id of the next process id to be assigned.
 */
Time ProcessSimulator::getSystemTime() const
{
  // task 1 this getter should return the member variable
  return systemTime;
}

/**
 * @brief num processes
 *
 * Accessor method to return the number of active processs currently under
 * management by the operating system simulation.  This count only includes
 * active processs (RUNNING, READY or BLOCKED).  It should not include a count
 * of processes that are finished.
 *
 * @returns int Returns the number of active processes that have not yet
 * finished.
 */
int ProcessSimulator::getNumActiveProcesses() const
{
  // task 1 this getter should return a dummy value until you implement
  // a process control block and/or actually create new processes and keep
  // track of the number of processes you have in the system somehow
  return processControlBlock.size() - 1;
}

/**
 * @brief num finished processes
 *
 * Accessor method to return the number of processes that were running but
 * have exited the simulation and are now DONE.
 *
 * @returns int Returns the number of finished processes that have gotten
 *   to the DONE state.
 */
int ProcessSimulator::getNumFinishedProcesses() const
{
  // task 1 this getter should return a dummy value until you implement
  // a process control block and/or actually create new processes and keep
  // track of the number of processes you have in the system somehow
  return numFinishedProcesses;
}

/**
 * @brief get process
 *
 * Accessor method, returns a reference to the Process indicated.  If
 * the pid is not a valid pid or indicates the IDLE process, an
 * empty/idle process is returned.
 *
 * @param pid The process identifier of the process currently being managed
 *   by the system to look up and return.
 *
 * @returns Process Retuns a reference to a Process object, which should be
 *   the process with the pid that was requested.
 */
Process& ProcessSimulator::getProcess(Pid pid)
{
  return processControlBlock[pid];
}

/**
 * @brief cpu running process
 *
 * Accessor method to return the Pid of the process currently
 * allocated the cpu and thus currently running on the cpu.
 * This method returns the IDLE pid if the cpu is currently
 * not allocated and is thus idle.
 *
 * @returns Pid Returns the process identifier of the process
 *   allocated the cpu.  If the cpu is currently idle, then the
 *   IDLE Pid identifier is returned.
 */

/**
 * @brief is cpu idle
 *
 * Accessor method returns true if the cpu is currently idle or false
 * otherwise.
 *
 * @returns bool true if cpu is currently IDLE and not allocated a process,
 *   false otherwise.
 */

/**
 * @brief ready queue size
 *
 * Accessor method returns current size of the ready queue.
 *
 * @returns int Returns the number of processes currently
 *   READY on the ready queue.
 */
int ProcessSimulator::readyQueueSize() const
{
  // can initially return 0, but at some point you need to implement a
  // ready queue and either keep track of the number of processes on the queue,
  // or use an accessor method of your queue, like ths size() method for an STL
  // list, to return the number of jobs on the queue.
  return readyQueue.size();
}

/**
 * @brief ready queue head
 *
 * Accessor method returns Pid of the current process at the
 * head of the ready queue.
 *
 * @returns Pid Returns the process identifier of the process
 *   at the head of the ready queue.  This function returns
 *   the IDLE Pid if the ready queue is empty.
 */
Pid ProcessSimulator::readyQueueFront() const
{
  // Initially this is hardcoded to return IDLE, but when you
  // implement your ready queue, you need to be able to get the front
  // process on the queue and return the pid of this process here
  if (readyQueue.empty())
  {
    return IDLE;
  }
  else
  {
    return readyQueue.front();
  }
}

/**
 * @brief ready queue back
 *
 * Accessor method returns Pid of the current process at the
 * back of the ready queue.
 *
 * @returns Pid Returns the process identifier of the process
 *   at the back end of the ready queue.  This function returns
 *   the IDLE Pid if the ready queue is empty.
 */
Pid ProcessSimulator::readyQueueBack() const
{
  // Initially this is hardcoded to return IDLE, but when you
  // implement your ready queue, you need to be able to get the back
  // process on the queue and return the pid of this process here
  if (readyQueue.empty())
  {
    return IDLE;
  }
  else
  {
    return readyQueue.back();
  }
}

/**
 * @brief blocked list size
 *
 * Accessor method returns current number of processes that
 * are in the BLOCKED state and thus are on the list or
 * whatever data structure is used to keep track of the blocked
 * processes in the system.
 *
 * @returns int Returns the number of processes currently
 *   BLOCKED in the system.
 */
int ProcessSimulator::blockedListSize() const
{
  // initially this should be hardcoded to return 0, but eventually you need
  // to have some data structure keeping track of the processes that are blocked
  // and be able to report the total number of blocked processes here
  return blockedList.size();
}

/**
 * @brief is cpu idle
 *
 * Accessor method returns true if the cpu is currently idle or false
 * otherwise.
 *
 * @returns bool true if cpu is currently IDLE and not allocated a process,
 *   false otherwise.
 */
bool ProcessSimulator::isCpuIdle() const
{
  return cpu == IDLE;
}

/**
 * @brief cpu running process
 *
 * Accessor method to return the Pid of the process currently
 * allocated the cpu and thus currently running on the cpu.
 * This method returns the IDLE pid if the cpu is currently
 * not allocated and is thus idle.
 *
 * @returns Pid Returns the process identifier of the process
 *   allocated the cpu.  If the cpu is currently idle, then the
 *   IDLE Pid identifier is returned.
 */
Pid ProcessSimulator::runningProcess() const
{
  return cpu;
}

/**
 * @brief test simulation state
 *
 * Convenience method for unit testing, test most of the important
 * simulation state in a single method.  This method should
 * reuse the individual accessor methods for each item, and
 * the actual logic to calculate the return value for each
 * state item should be done there.
 *
 * @param timeSliceQuantum The expected setting of the system timeSliceQuantum.
 * @param systemTime The expected current system time of the simulation.
 * @param numActiveProcesses The expected number of active processes currently
 *   managed by the simulation.
 * @param numFinishedProcesses The expected number of processes that have
 *   finished the simulation.
 * @param runningProcess The Pid of the current process allocated to and running
 *   on the cpu.
 * @param readyQueueSize The expected number of processes currently on the
 *   ready queue.
 * @param readyQueueFront The Pid of the process we expect to be at the
 *   head of the ready queue.
 * @param readyQueueBack The Pid of the process we expect to be at the
 *   tail of the ready queue.
 * @param blockedListSize The expected number of processes that should be
 *   in the blocked state in the system.
 *
 * @returns bool true if the simulation exactly matches the expected
 *   state, false otherwise.
 */
bool ProcessSimulator::isInState(Time timeSliceQuantum, Time systemTime, int numActiveProcesses, int numFinishedProcesses,
  Pid runningProcess, int readyQueueSize, Pid readyQueueFront, Pid readyQueueBack, int blockedListSize)
{
  bool stateIsCorrect = (timeSliceQuantum == this->getTimeSliceQuantum()) and (systemTime == this->getSystemTime()) and
                        (numActiveProcesses == this->getNumActiveProcesses()) and
                        (numFinishedProcesses == this->getNumFinishedProcesses()) and (runningProcess == cpu) and
                        (readyQueueSize == this->readyQueueSize()) and (readyQueueFront == this->readyQueueFront()) and
                        (readyQueueBack == this->readyQueueBack()) and (blockedListSize == this->blockedListSize());

  // if the state was correct, we just return true
  if (stateIsCorrect)
  {
    return true;
  }
  // otherwise we first display the actual state of this process to
  // stdout, to help with debugging of the test that failed.
  else
  {
    cout << *this << endl;
    return false;
  }
}

/**
 * @brief simulation new event
 *
 * Perform tasks needed whenever a "new" even occurs in the simulation.
 * A new event should cause:
 *   - A new process to be created and the process added to the process control
 *     list or process control block of the system.
 *   - New process is initialized with the current system time and other init
 *     information as needed.
 *   - The new process is put into the READY state.
 *   - The new process is added to the back of the ready queue.
 *   - Update the next process id for next new process creation.
 */
void ProcessSimulator::newEvent()
{
  Pid pid = nextProcessId;
  Process newProcess(pid, systemTime);
  newProcess.ready();
  processControlBlock[pid] = newProcess;
  readyQueue.push_back(pid);
  nextProcessId++;
}

/**
 * @brief dispatch process
 *
 * Check if a process should be dispatch and dispatch a process if we can.
 * This function has several tasks to perform.
 *   - If cpu is not IDLE then we do nothing
 *   - Otherwise if ready queue is not empty then dispatch the process at the
 * front of the queue So this function can do nothing, can cause a process to be
 * removed from the ready queue and become the running process.  Or if the ready
 * queue is empty then the cpu can still be IDLE after this function finishes.
 */
void ProcessSimulator::dispatch()
{
  // if the cpu is currently running a process, dispatch does nothing
  if (not isCpuIdle())
  {
    return;
  }

  // if the cpu is idle, but no processes are ready to run, we still do
  // nothing
  if (readyQueueFront() == IDLE)
  {
    return;
  }

  // otherwise cpu is idle and 1 or more processes ready, so dispatch
  // process at front of queue
  Pid pid = readyQueueFront();
  readyQueue.pop_front();
  cpu = pid;
  processControlBlock[pid].dispatch();
}

/**
 * @brief cpu simulation event
 *
 * Simulate a cpu cycle.  We increment the timeUsed and quantumUsed
 * for the current running process (it there is one).
 */
void ProcessSimulator::cpuEvent()
{
  // increment the system time
  systemTime++;

  // if a process is currently running, update its work
  if (not isCpuIdle())
  {
    processControlBlock[cpu].cpuCycle();
  }
}

/**
 * @brief timeout process
 *
 * Check if current running process has exceeded its time slice quantum, and if
 * so Time it out and return it back to the ready queue.  This function performs
 * the following tasks:
 *   - If cpu is idle then nothing to do
 *   - Otherwise test quantum used of running cpu
 *     - If it exceeds the time slice quantum, put back into ready state and
 *     - push to tbe back of the ready queue.
 */
void ProcessSimulator::timeout()
{
  // if cpu is idle, nothing to do
  if (isCpuIdle())
  {
    return;
  }

  // otherwise test if running process has exceeded the system time
  // slice quantum
  if (processControlBlock[cpu].isQuantumExceeded(timeSliceQuantum))
  {
    processControlBlock[cpu].timeout();
    readyQueue.push_back(cpu);
    cpu = IDLE;
  }
}

/**
 * @brief block event
 *
 * Handle tasks necessary to simulate processes being blocked waiting on I/O
 * or other types of system events to occur.  If a process is currently running
 * then cause it to become blocked and removed from the cpu.  We consider it
 * a simulation error for a block event to occur if no process is currently
 * running on the cpu (it doesn't make sense for a simulation to have blocking
 * events but no associated process that should be blocked).  An exception is
 * thrown if block is called in simulation when the cpu is idle.
 *
 * @param eventId The identifier of the event that the current running process
 *   needs to block on and wait to occur.
 *
 * @throws SimulatorException is thrown if a block is attempted when the
 *   cpu is idle or if there is already a process waiting on this event.
 */
void ProcessSimulator::blockEvent(EventId eventId)
{
  // if the cpu is currently idle, then no process to block on this event, we
  // consider this an invalid thing to happen in these simulations, so throw
  // an exception if it happens
  if (isCpuIdle())
  {
    stringstream msg;
    msg << "<ProcessSimulator::blockEvent>"
        << "     Error: blockEvent occurred when cpu is idle, block on event: " << eventId;
    throw SimulatorException(msg.str());
  }

  // it is also an error if there is already a process currently waiting on this
  // event
  if (blockedList.count(eventId) >= 1)
  {
    stringstream msg;
    msg << "<ProcessSimulator::blockEvent>"
        << "     Error: blockEvent occurred process is already blocked on the event" << endl
        << "     event: " << eventId << endl
        << "   process: " << blockedList[eventId] << endl;

    throw SimulatorException(msg.str());
  }

  // otherwise block the current running process
  processControlBlock[cpu].block(eventId);

  // and add this process to the blocked list
  blockedList[eventId] = cpu;

  // finally, the cpu is now idle because the current running
  // process just blocked
  cpu = IDLE;
}

/**
 * @brief unblock event
 *
 * Handle tasks necessary to simulate processes being unblocked when the
 * I/O or system event they are waiting on occurs.
 *
 * @param eventId The identifier of the event that occurred that should unblock
 *   a waiting process.
 *
 * @throws SimulatorException is thrown if an unblock is attempted when the
 *   no process is waiting on that event type.
 */
void ProcessSimulator::unblockEvent(EventId eventId)
{
  // it is  an error if there is no process waiting on the indicated event
  if (blockedList.count(eventId) == 0)
  {
    stringstream msg;
    msg << "<ProcessSimulator::unblockEvent>"
        << "     Error: unblockEvent occurred when no process waiting on the event" << endl
        << "     event: " << eventId << endl;

    throw SimulatorException(msg.str());
  }

  // otherwise unblock the process
  Pid pid = blockedList[eventId];
  processControlBlock[pid].unblock();

  // put this process back onto the ready queue
  readyQueue.push_back(pid);

  // and remove this key/value mapping from the blocked list
  blockedList.erase(blockedList.find(eventId));
}

/**
 * @brief done event
 *
 * Handle tasks necessary to simulate processes finishing and exiting the
 * system. Need to keep track of any statistics needed for the simulation
 * output, then mark or remove the process from the process control block.  The
 * done event should only happen when a process is currently running on the cpu.
 * Thus it doesn't make sense in this simulation to receive a done event when
 * the cpu is idle.  We throw an exception if we see done events when the cpu is
 * idle.
 *
 * @throws SimulatorException is thrown if a done is attempted when the
 *   cpu is idle.
 */
void ProcessSimulator::doneEvent()
{
  // if the cpu is currently idle, then it is considered an error in the
  // simulation for a done event to occur
  if (isCpuIdle())
  {
    stringstream msg;
    msg << "<ProcessSimulator::doneEvent>"
        << "   Error: done event occurred when cpu is IDLE";
    throw SimulatorException(msg.str());
  }

  // otherwise the current running process is now done, remove it from the
  // process control block
  processControlBlock.erase(processControlBlock.find(cpu));

  // update count of number of finished processes
  numFinishedProcesses++;

  // finally the cpu is now idle since the current running process finished
  cpu = IDLE;
}

/**
 * @brief run simulation file
 *
 * Run a full ProcessSimulator simulation.  Using the provided file
 * which defines events in the order they occur in the simulation,
 * open the file, read in the events, and use this simulator object
 * to simulate the results of the given process events.
 *
 * @param simulationFile The name of the simulation file that should be
 *   opened and read in for the event sequence to simulate.
 */
void ProcessSimulator::runSimulation(string simulationFile)
{
  ifstream simulationStream;

  // open the file as a stream for reading, error check that file
  // loadeed successfully
  simulationStream.open(simulationFile.c_str());
  if (not simulationStream.is_open())
  {
    stringstream msg;
    msg << "<ProcessSimulator::runSimulation>"
        << " Error: could not open simulation file: " << simulationFile;
    throw SimulatorException(msg.str());
  }

  // read simulation events from file.  each line of file contains 1 event
  // to process and simulate
  string event;
  EventId eventId;

  while (simulationStream >> event)
  {
    /* Task 9 / system tests  Uncomment the following calls to the
       ProcessSimulator member functions you have implemented
    */

    // before next event, determine if we need to dispatch a process
    // and schedule it to run
    dispatch();

    // handle the next simulated event
    if (event == "new")
    {
      newEvent();
    }
    else if (event == "cpu")
    {
      cpuEvent();
    }
    else if (event == "block")
    {
      simulationStream >> eventId;
      blockEvent(eventId);
    }
    else if (event == "unblock")
    {
      simulationStream >> eventId;
      unblockEvent(eventId);
    }
    else if (event == "done")
    {
      doneEvent();
    }
    else
    {
      stringstream msg;
      msg << "<ProcessSimulator::runSimulation>"
          << " Error: uknown simulation event received: " << event;
      throw SimulatorException(msg.str());
    }

    // after event, determine if the current running event needs to be
    // timed out and returned to back of the ready queue
    timeout();

    // display current simulation system state to standard output
    cout << "------------------------------------------------------------------"
            "------"
         << endl;
    cout << "Event: " << event;
    if ((event == "block") or (event == "unblock"))
    {
      cout << " EventId: " << eventId;
    }
    cout << endl << endl;
    cout << *this;
  }

  // close file cleanly to exit
  simulationStream.close();
}

/**
 * @brief string representation
 *
 * Create a string representation of the current state of this
 * simulator object.  This method is used by the overloaded
 * output operator<< to send the status of the simulation
 * to an output stream.
 *
 * @returns string Returns a string object that contains information
 *   about the current state of this process simulator.
 */
string ProcessSimulator::toString() const
{
  stringstream stream;

  stream << "<Simulation> system time: " << systemTime << endl
         << "  timeSliceQuantum      : " << timeSliceQuantum << endl
         << "  numActiveProcesses    : " << getNumActiveProcesses() << endl
         << "  numFinishedProcesses  : " << getNumFinishedProcesses() << endl
         << endl
         << "  CPU" << endl
         << "    " << processControlBlock.at(cpu) << endl
         << "  CPU" << endl
         << endl;

  // display the ready queue
  stream << "  Ready Queue Head" << endl;
  for (Pid pid : readyQueue)
  {
    stream << "    " << processControlBlock.at(pid) << endl;
  }
  stream << "  Ready Queue Tail" << endl << endl;

  // display the blocked list
  stream << "  Blocked List" << endl;
  for (auto& keyValuePair : blockedList)
  {
    // EventId eventId = keyValuePair.first;
    Pid pid = keyValuePair.second;
    stream << "    " << processControlBlock.at(pid) << endl;
  }
  stream << "  Blocked List" << endl << endl;

  // convert our string stream back to a regular string for return to caller
  return stream.str();
}

/** ProcessSimulator output operator
 * Overload the output operator for a ProcesSimulator object.
 * This function allows us to directly stream a ProcessSimulator
 * object into an output stream.
 *
 * @param stream A reference to the output stream we are to
 *    output the representation of the ProcessState.
 * @param sim A reference to the ProcessSimulator we are streaming to
 *    the output stream.
 *
 * @returns ostream& Returns a reference to the (modified) output
 *    stream that we wrote the ProcessSimulator into.
 */
ostream& operator<<(ostream& stream, const ProcessSimulator& sim)
{
  stream << sim.toString();

  return stream;
}
