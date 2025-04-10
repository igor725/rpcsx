#pragma once

#include "orbis/KernelAllocator.hpp"
#include "orbis/file.hpp"
#include "orbis/utils/Rc.hpp"
#include <cstdint>

enum OpenFlags {
  kOpenFlagReadOnly = 0x0,
  kOpenFlagWriteOnly = 0x1,
  kOpenFlagReadWrite = 0x2,
  kOpenFlagNonBlock = 0x4,
  kOpenFlagAppend = 0x8,
  kOpenFlagShLock = 0x10,
  kOpenFlagExLock = 0x20,
  kOpenFlagAsync = 0x40,
  kOpenFlagFsync = 0x80,
  kOpenFlagCreat = 0x200,
  kOpenFlagTrunc = 0x400,
  kOpenFlagExcl = 0x800,
  kOpenFlagDSync = 0x1000,
  kOpenFlagDirect = 0x10000,
  kOpenFlagDirectory = 0x20000,
};

struct IoDevice : orbis::RcBase {
  virtual orbis::ErrorCode open(orbis::Ref<orbis::File> *file, const char *path,
                                std::uint32_t flags, std::uint32_t mode,
                                orbis::Thread *thread) = 0;
  virtual orbis::ErrorCode unlink(const char *path, orbis::Thread *thread) {
    return orbis::ErrorCode::NOTSUP;
  }
};

IoDevice *createHostIoDevice(orbis::kstring hostPath);
orbis::ErrorCode createSocket(orbis::Ref<orbis::File> *file,
                              orbis::kstring name, int dom, int type, int prot);
orbis::File *createHostFile(int hostFd, orbis::Ref<IoDevice> device);
IoDevice *createFdWrapDevice(int fd);
