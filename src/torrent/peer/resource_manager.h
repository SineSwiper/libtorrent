// libTorrent - BitTorrent library
// Copyright (C) 2005-2007, Jari Sundell
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// In addition, as a special exception, the copyright holders give
// permission to link the code of portions of this program with the
// OpenSSL library under certain conditions as described in each
// individual source file, and distribute linked combinations
// including the two.
//
// You must obey the GNU General Public License in all respects for
// all of the code used other than OpenSSL.  If you modify file(s)
// with this exception, you may extend this exception to your version
// of the file(s), but you are not obligated to do so.  If you do not
// wish to do so, delete this exception statement from your version.
// If you delete this exception statement from all source files in the
// program, then also delete it here.
//
// Contact:  Jari Sundell <jaris@ifi.uio.no>
//
//           Skomakerveien 33
//           3185 Skoppum, NORWAY

#ifndef LIBTORRENT_PEER_RESOURCE_MANAGER_H
#define LIBTORRENT_PEER_RESOURCE_MANAGER_H

#include <vector>
#include <inttypes.h>
#include <torrent/common.h>

namespace torrent {

// This class will handle the division of various resources like
// uploads. For now the weight is equal to the value of the priority.
//
// Although the ConnectionManager class keeps a tally of open sockets,
// we still need to balance them across the different downloads so
// ResourceManager will also keep track of those.
//
// Add unlimited handling later.

class DownloadMain;
class ResourceManager;

class LIBTORRENT_EXPORT resource_manager_entry {
public:
  friend class ResourceManager;

  resource_manager_entry(DownloadMain* d = NULL, uint16_t p = 0) : m_download(NULL), m_priority(0) {}

  DownloadMain*       download()         { return m_download; }
  const DownloadMain* c_download() const { return m_download; }
  uint16_t            priority() const   { return m_priority; }

protected:
  void                set_priority(uint16_t p) { m_priority = p; }

private:
  DownloadMain*       m_download;

  // TODO: Deprecate this when we move to more refined groupings.
  //
  // Change set_priority before adding more variables.
  uint16_t            m_priority;
};


class LIBTORRENT_EXPORT ResourceManager : public std::vector<resource_manager_entry> {
public:
  typedef std::vector<resource_manager_entry> base_type;
  typedef base_type::value_type               value_type;
  typedef base_type::iterator                 iterator;

  using base_type::begin;
  using base_type::end;

  ResourceManager() :
    m_currentlyUploadUnchoked(0),
    m_currentlyDownloadUnchoked(0),
    m_maxUploadUnchoked(0),
    m_maxDownloadUnchoked(0) {}
  ~ResourceManager();

  void                insert(DownloadMain* d, uint16_t priority) { insert(value_type(d, priority)); }
  void                erase(DownloadMain* d);

  iterator            find(DownloadMain* d);
  void                set_priority(iterator itr, uint16_t pri);

  // When setting this, make sure you choke peers, else change
  // receive_can_unchoke.
  unsigned int        currently_upload_unchoked() const         { return m_currentlyUploadUnchoked; }
  unsigned int        currently_download_unchoked() const       { return m_currentlyDownloadUnchoked; }

  unsigned int        max_upload_unchoked() const               { return m_maxUploadUnchoked; }
  unsigned int        max_download_unchoked() const             { return m_maxDownloadUnchoked; }

  void                set_max_upload_unchoked(unsigned int m);
  void                set_max_download_unchoked(unsigned int m);

  void                receive_upload_unchoke(int num);
  void                receive_download_unchoke(int num);

  unsigned int        retrieve_upload_can_unchoke();
  unsigned int        retrieve_download_can_unchoke();

  void                receive_tick();

private:
  iterator            insert(const resource_manager_entry& entry);

  unsigned int        total_weight() const;

  void                balance_upload_unchoked(unsigned int weight);
  void                balance_download_unchoked(unsigned int weight);

  unsigned int        m_currentlyUploadUnchoked;
  unsigned int        m_currentlyDownloadUnchoked;

  unsigned int        m_maxUploadUnchoked;
  unsigned int        m_maxDownloadUnchoked;
};

}

#endif