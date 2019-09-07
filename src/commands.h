//
// Created by smyck on 07/09/2019.
//

#ifndef NVMAN_COMMANDS_H
#define NVMAN_COMMANDS_H

int show_info();

void show_usage();

int delete(const char *appName, const char *titleName);

int lock(const char *appName, const char *titleName);

int unlock(const char *appName, const char *titleName);

int create(const char *appName, const char *titleName);

#endif //NVMAN_COMMANDS_H
