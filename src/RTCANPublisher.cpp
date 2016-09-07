/* COPYRIGHT (c) 2016 Nova Labs SRL
 *
 * All rights reserved. All use of this software and documentation is
 * subject to the License Agreement located in the file LICENSE.
 */

#include <core/mw/namespace.hpp>
#include <core/mw/transport/RTCANPublisher.hpp>

NAMESPACE_CORE_MW_BEGIN


RTCANPublisher::RTCANPublisher(
   Transport& transport
)
   :
   RemotePublisher(transport)
{}


RTCANPublisher::~RTCANPublisher() {}


NAMESPACE_CORE_MW_END
