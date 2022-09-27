/**
 * @author Jane Student
 * @cwid   123 45 678
 * @class  CSci 530, Summer 2015
 * @ide    Visual Studio Express 2010
 * @date   June 8, 2015
 * @assg   prog-04
 *
 * @description This program implements a simulation of process
 *    scheduling policies.  In this program, we implement round-robin
 *    scheduling, where the time slice quantum can be specified as
 *    as a command line parameter.  And we also implement shortest
 *    remaining time (SRT) scheduling policy
 */
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <list>
using namespace std;


// global constants
// I won't test your round robin implementation with more than 20 processes
const int MAX_PROCESSES = 20;
const int NO_PROCESS = 0;

// Simple structure, holds all of the information about processes, their names
// arrival and service times, that we are to simulate.
typedef struct
{
  string processName;
  int arrivalTime;
  int serviceTime;
  // holds running count of time slices for current time quantum, when
  // serviceTime == quantum, time slice is up
  int sliceTime;
  // holds total number of time steps currently run, when == to
  // serviceTime process is done
  int totalTime;
  // holds time when process finishes, used to calculate final stats,
  // like T_r, T_r/T_s
  int finishTime; 
  // a boolean flag, we will set this to true when the process is complete
  bool finished;
} Process;

// Process table, holds table of information about processes we are simulating
typedef struct
{
  int numProcesses;
  Process* process[MAX_PROCESSES];
} ProcessTable;


/** Create process table
 * Allocate memory for a new process table.  Load the process
 * information from the simulation file into a table with the process
 * information needed to perform the simulation.  At the same time we
 * initialize other information in process table for use in the
 * simulation.  Return the newly created ProcessTable
 *
 * @param processFilanem The name (char*) of the file to open and read
 *         the process information from.
 * @param processTable This is actually a return parameter.  This
 *         should be a pointer to an already allocated array of
 *         Process structure items.  We will fill in this structure
 *         and return the process information.
 *
 * @returns ProcessTable* The newly allocated and initialized ProcessTable
 *         structure.
 */
ProcessTable* createProcessTable(char* processFilename)
{
  ifstream simprocessfile(processFilename);
  ProcessTable* processTable;
  int pid;
  string processName;
  int arrivalTime;
  int serviceTime;

  // If we can't open file, abort and let the user know problem
  if (!simprocessfile.is_open())
  {
    cout << "Error: could not open process simulation file: " 
         << processFilename << endl;
    exit(1);
  }
  
  // Format of file is
  // ProcessName1 ArrivalTime1 ServiceTime1
  // ProcessName2 ArrivalTime2 ServiceTime2
  // ...
  // ProcessNameN ArrivalTimeN ServiceTimeN
  //
  // Where the name is any arbitray string identifier, and ArrivalTime
  // and ServiceTime are integer values
  pid = 0;
  processTable = new(ProcessTable);
  while (simprocessfile >> processName >> arrivalTime >> serviceTime)
  {
    // allocate a new process to hold information
    Process* process = new(Process);
    processTable->process[pid] = process;

    // load information into process read from simulation file
    process->processName = processName;
    process->arrivalTime = arrivalTime;
    process->serviceTime = serviceTime;

    // initialize other process information for the simulaiton
    process->sliceTime = 0; 
    process->totalTime = 0; 
    process->finishTime = 0; 
    process->finished = false;

    pid++;
  }

  // Set the number of processes we need to simulate information in
  // the process table
  processTable->numProcesses = pid;

  return processTable;
}


/** Display process table
 * Convenience method, dump all of the information about the processes
 * in a process table to stdout.
 *
 * @param processTable The table, a pointer to type ProcessTable
 *           struct, with the information we are to display
 */
void displayProcessTable(ProcessTable* processTable)
{
  cout << "Process Table num = " << processTable->numProcesses << endl;
  cout << "PID Name Arrv Srvc" << endl;
  cout << "------------------" << endl;
  for (int pid=0; pid < processTable->numProcesses; pid++)
  {
    Process* p = processTable->process[pid];
    cout << setw(2) << right << pid << ") ";
    cout << setw(4) << left << p->processName << " ";
    cout << setw(4) << right << p->arrivalTime << " ";
    cout << setw(4) << right << p->serviceTime << " ";
    cout << endl;
  }
}


/** Round robin scheduler simulator
 * The main routine for performing the round robin preemptive
 * scheduler simulator.  We expect the time quantum to already be
 * specified and given to us as the first parameter.  The file name
 * with the process arrival and service time information is given as
 * the second parameter.  We simulate preemptive round robin
 * scheduling of all of the processes until there are no longer any
 * processes left in the system (all processes have exceeded their
 * service time and have exited).
 *
 * @param processTable A pointer to a ProcessTable structure holding
 *      information about the processes, arrival times and durations
 *      that we are simulating execution of.
 * @param quantum An integer value holding the time slice quantum we
 *      are using for this simulation.
 */
void roundRobinScheduler(ProcessTable* processTable, int quantum)
{
  // Implement the round robin scheduler here
  cout << "<roundRobinScheduler> entered, quantum: " << quantum << endl;
}


/** shortest remaining time simulator
 * The main routine for performing the shortest remaining time
 * preemptive scheduler simulator.  The file name with the process
 * arrival and service time information is given as the first
 * parameter.  We simulate preemptive shortest remaining time
 * scheduling of all of the processes until there are no longer any
 * processes left in the system (all processes have exceeded their
 * service time and have exited).
 *
 * @param processTable A pointer to a ProcessTable structure holding
 *      information about the processes, arrival times and durations
 *      that we are simulating execution of.
 */
void shortestRemainingTime(ProcessTable* processTable)
{
  // Implement the shortest remaining time policy here
  cout << "<shortestRemainingTime> entered" << endl;
}


/** Main entry point of round robin scheduler
 * The main entry point of the round robin scheduler simulator.  The main funciton
 * checks the command line arguments, and calls the simulation function if correct
 * arguments were supplied.   We expect two command line arguments, which are the
 * time slice quantum value we are to use for this preemptive scheduler simulation,
 * and the name of the simulation file holding the process arrival and service
 * time information.
 *
 * @param argc The argument count
 * @param argv The command line argument values. We expect argv[1] to be the
 *              time slice quantum parameter (int format) and argv[2] to be the
 *              name of the process simulation file (charcter string)
 */
int main(int argc, char** argv)
{
  string policy;
  ProcessTable* processTable;
  int quantum = 0;

  // If not all parameters provides, abort and let user know of problem
  if (argc < 3 || argc > 4)
  {
    cout << "Error: expecting process simulation file and scheduling policy as command line parameters"
	 << endl;
    cout << "Usage: " << argv[0] << " process-file.sim [rr|srt] [quantum]" << endl;
    exit(1);
  }

  // load process table and parse command line arguments
  processTable = createProcessTable(argv[1]);
  // just to confirm that process table loaded correctly.  You should
  // comment out or remove this as it is not asked for as part of the
  // output for the assignment simulation
  displayProcessTable(processTable);

  // determine policy to simulate
  policy.assign(argv[2]);

  // perform simulation of indicated scheduling policy
  if (policy == "rr")
  {
    if (argc != 4)
    {
      cout << "Error: time quantum must be provided for round robin `rr` scheduling policy" << endl;
      exit(1);
    }
    quantum = atoi(argv[3]);
    if ( (quantum <= 0) || (quantum > 1000) )
    {
      cout << "Error: received bad time slice quantum parameter: " << argv[1] << endl;
      cout << "       valid values are integers in range from 1 to 1000" << endl;
      exit(1);
    }

    roundRobinScheduler(processTable, quantum);
  }
  else if (policy == "srt")
  {
    shortestRemainingTime(processTable);
  }
  else
  {
    cout << "Error: unknown process scheduling policy: " << policy << endl;
  }
}
