
TESTS = LibTorrentTest
check_PROGRAMS = $(TESTS)
LibTorrentTest_LDADD = \
	../src/libtorrent.la \
	../src/torrent/libsub_torrent.la \
	../src/torrent/data/libsub_torrentdata.la \
	../src/torrent/download/libsub_torrentdownload.la \
	../src/torrent/peer/libsub_torrentpeer.la \
	../src/torrent/utils/libsub_torrentutils.la \
	../src/data/libsub_data.la \
	../src/dht/libsub_dht.la \
	../src/download/libsub_download.la \
	../src/net/libsub_net.la \
	../src/protocol/libsub_protocol.la \
	../src/tracker/libsub_tracker.la \
	../src/utils/libsub_utils.la

LibTorrentTest_SOURCES = \
	rak/allocators_test.cc \
	rak/allocators_test.h \
	rak/ranges_test.cc \
	rak/ranges_test.h \
	torrent/extents_test.cc \
	torrent/extents_test.h \
	torrent/http_test.cc \
	torrent/http_test.h \
	torrent/object_test.cc \
	torrent/object_test.h \
	torrent/object_test_utils.cc \
	torrent/object_test_utils.h \
	torrent/object_static_map_test.cc \
	torrent/object_static_map_test.h \
	torrent/object_stream_test.cc \
	torrent/object_stream_test.h \
	torrent/tracker_controller_test.cc \
	torrent/tracker_controller_test.h \
	torrent/tracker_list_test.cc \
	torrent/tracker_list_test.h \
	torrent/tracker_timeout_test.cc \
	torrent/tracker_timeout_test.h \
	torrent/utils/log_test.cc \
	torrent/utils/log_test.h \
	torrent/utils/option_strings_test.cc \
	torrent/utils/option_strings_test.h \
	torrent/utils/thread_base_test.cc \
	torrent/utils/thread_base_test.h \
	tracker/tracker_http_test.cc \
	tracker/tracker_http_test.h \
	main.cc

LibTorrentTest_CXXFLAGS = $(CPPUNIT_CFLAGS)
LibTorrentTest_LDFLAGS = $(CPPUNIT_LIBS)  -ldl

INCLUDES = -I$(srcdir) -I$(top_srcdir) -I$(top_srcdir)/src
