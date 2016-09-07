/* COPYRIGHT (c) 2016 Nova Labs SRL
 *
 * All rights reserved. All use of this software and documentation is
 * subject to the License Agreement located in the file LICENSE.
 */

#pragma once

#include <core/mw/namespace.hpp>
#include <core/common.hpp>
#include <core/mw/Transport.hpp>
#include <core/mw/BaseSubscriberQueue.hpp>
#include <core/mw/TimestampedMsgPtrQueue.hpp>
#include <core/os/Mutex.hpp>
#include <core/mw/MgmtMsg.hpp>
#include <core/mw/BootMsg.hpp>
#include <core/os/Semaphore.hpp>
#include <core/os/Thread.hpp>
#include <core/os/MemoryPool.hpp>

#include "rtcan.h"
#include "RTCANPublisher.hpp"
#include "RTCANSubscriber.hpp"


NAMESPACE_CORE_MW_BEGIN

class Message;

class RTCANTransport:
   public Transport
{
private:
   RTCANDriver& rtcan;
   // FIXME to move in pub/sub?
   rtcan_msg_t header_buffer[10];
   core::os::MemoryPool<rtcan_msg_t> header_pool;

   BaseSubscriberQueue subp_queue;

   enum {
      MGMT_BUFFER_LENGTH = 4
   };

   MgmtMsg mgmt_msgbuf[MGMT_BUFFER_LENGTH];
   TimestampedMsgPtrQueue::Entry mgmt_msgqueue_buf[MGMT_BUFFER_LENGTH];
   RTCANSubscriber* mgmt_rsub;
   RTCANPublisher*  mgmt_rpub;

#if CORE_IS_BOOTLOADER_BRIDGE
   enum {
      BOOT_BUFFER_LENGTH = 4
   };

   BootMsg boot_msgbuf[BOOT_BUFFER_LENGTH];
   TimestampedMsgPtrQueue::Entry boot_msgqueue_buf[BOOT_BUFFER_LENGTH];
   RTCANSubscriber* boot_rsub;
   RTCANPublisher*  boot_rpub;
#endif

public:
   bool
   send(
      Message*         msgp,
      RTCANSubscriber* rsubp
   );

   rtcan_id_t
   topic_id(
      const Topic& topic
   ) const;                    // FIXME

   void
   initialize(
      const RTCANConfig& rtcan_config
   );

   void
   fill_raw_params(
      const Topic& topic,
      uint8_t      raw_params[]
   );


private:
   RemotePublisher*
   create_publisher(
      Topic&        topic,
      const uint8_t raw_params[] = NULL
   ) const;

   RemoteSubscriber*
   create_subscriber(
      Topic&                        topic,
      TimestampedMsgPtrQueue::Entry queue_buf[], // TODO: remove
      size_t                        queue_length
   ) const;


public:
   RTCANTransport(
      RTCANDriver& rtcan
   );
   ~RTCANTransport();

private:
   static void
   send_cb(
      rtcan_msg_t& rtcan_msg
   );

   static void
   recv_cb(
      rtcan_msg_t& rtcan_msg
   );

   static void
   free_header(
      rtcan_msg_t& rtcan_msg
   );
};

NAMESPACE_CORE_MW_END
