/* Copyright 2012-present Facebook, Inc.
 * Licensed under the Apache License, Version 2.0 */
#pragma once

struct watchman_stat {
  struct timespec atime, mtime, ctime;
  off_t size;
  mode_t mode;
  uid_t uid;
  gid_t gid;
  ino_t ino;
  dev_t dev;
  nlink_t nlink;
};

struct watchman_dir_ent {
  bool has_stat;
  char *d_name;
  struct watchman_stat stat;
};

class watchman_dir_handle {
 public:
  virtual ~watchman_dir_handle() = default;
  virtual const watchman_dir_ent* readDir() = 0;
#ifndef _WIN32
  virtual int getFd() const = 0;
#endif
};

// Return a dir handle on path.
// Does not follow symlinks.
// Throws std::system_error if the dir could not be opened.
std::unique_ptr<watchman_dir_handle> w_dir_open(const char* path);
