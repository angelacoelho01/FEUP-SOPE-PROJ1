#ifndef SRC_LOGGER_H_
#define SRC_LOGGER_H_

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../src/utils.h"	

#define PROC_CREAT "PROC_CREAT"
#define PROC_EXIT "PROC_EXIT"
#define SIGNAL_RECV "SIGNAL_RECV"
#define SIGNAL_SENT "SIGNAL_SENT"
#define FILE_MODF "FILE_MODF"

/**
 * @brief Checks if the environment variable LOG_FILENAME is defined and, in that case, to open log file whose
 * path is determined by LOG_FILENAME.
 * 
 * @return int the file descriptor on success, 0 in case LOF_FILENAME is not defined or -1 if an error occured
 */
int openLogger();

/**
 * @brief Writes to the log file, that was already opened, information (instant, pid, action and info) about each
 * process involved during execution.
 * 
 * @param pid the process id or the group id
 * @param event the event associated to that process
 * @param info the id of the type of event that affected the process
 * @return int additional information associated to the event
 */
int writeToLogger(int pid, const char *event, const char *info);

/**
 * @brief Closes the log file after saving all the information of the involved processes.
 * 
 * @return int 0 on success, or -1 on error
 */
int closeLogger();

/**
 * @brief Gets additional information of a process that has received a certain signal.
 * 
 * @param signal the signal name
 * @param pid the process id
 * @return char* the string with the additional information ready to be written on log file
 */
char* getInfoSig(const char *signal, const pid_t pid);

/**
 * @brief Gets additional information of a group that has received a certain signal.
 * 
 * @param signal the signal name
 * @param gid the group id
 * @return char* the string with the additional information ready to be written on log file
 */
char* getGroupInfoSig(const char *signal, pid_t gid);

/**
 * @brief Gets the additional information of a file that had its permissions modified.
 * 
 * @param path the file path
 * @return char* the string with the additional information ready to be written on log file
 */
char *getInfoFModf(const char *path);

#endif // SRC_LOGGER_H_