#ifndef NVMAN_COMMANDS_H
#define NVMAN_COMMANDS_H

int show_info();

void show_usage();

int delete(const char *appName, const char *titleName, BOOL force);

int lock(const char *appName, const char *titleName);

int unlock(const char *appName, const char *titleName);

int create(const char *appName, const char *titleName, BOOL force);

int delete_all(BOOL force);

#endif //NVMAN_COMMANDS_H
