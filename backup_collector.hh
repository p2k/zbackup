// Copyright (c) 2012-2014 Konstantin Isakov <ikm@zbackup.org> and ZBackup contributors, see CONTRIBUTORS
// Part of ZBackup. Licensed under GNU GPLv2 or later + OpenSSL, see LICENSE

#ifndef BACKUP_COLLECTOR_HH_INCLUDED
#define BACKUP_COLLECTOR_HH_INCLUDED

#include "zbackup_base.hh"
#include "chunk_storage.hh"

#include <string>
#include <vector>
#include <unistd.h>

#include "bundle.hh"
#include "chunk_index.hh"
#include "backup_restorer.hh"
#include "backup_file.hh"
#include "backup_exchanger.hh"

#include "debug.hh"

using std::string;

class BundleCollector: public IndexProcessor
{
private:
  Bundle::Id savedId;
  int totalChunks, usedChunks, indexTotalChunks, indexUsedChunks;
  int indexModifiedBundles, indexKeptBundles, indexRemovedBundles;
  vector< string > filesToUnlink;

public:
  bool indexModified;
  string bundlesPath;
  bool verbose;
  ChunkStorage::Reader *chunkStorageReader;
  ChunkStorage::Writer *chunkStorageWriter;
  BackupRestorer::ChunkSet usedChunkSet;

  void startIndex( string const & indexFn );

  void finishIndex( string const & indexFn );

  void startBundle( Bundle::Id const & bundleId );

  void processChunk( ChunkId const & chunkId );

  void finishBundle( Bundle::Id const & bundleId, BundleInfo const & info );

  void commit();
};

#endif
