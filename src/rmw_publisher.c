// Copyright 2022 Washington University in St Louis
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#include "rmw/error_handling.h"
#include "rmw/rmw.h"
#include "rmw/get_node_info_and_types.h"
#include "rmw/get_service_names_and_types.h"
#include "rmw/get_topic_endpoint_info.h"
#include "rmw/get_topic_names_and_types.h"
#include "rmw/names_and_types.h"
#include "rmw/sanity_checks.h"
#include "rmw/validate_namespace.h"
#include "rmw/validate_node_name.h"

#include "rmw_hazcat/allocators/cpu_ringbuf_allocator.h"
#include "rmw_hazcat/hazcat_message_queue.h"

#ifdef __cplusplus
extern "C"
{
#endif
rmw_ret_t
rmw_init_publisher_allocation(
  const rosidl_message_type_support_t * type_support,
  const rosidl_runtime_c__Sequence__bound * message_bounds,
  rmw_publisher_allocation_t * allocation)
{
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(type_support, RMW_RET_INVALID_ARGUMENT);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(message_bounds, RMW_RET_INVALID_ARGUMENT);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(allocation, RMW_RET_INVALID_ARGUMENT);

  RMW_SET_ERROR_MSG("rmw_init_publisher_allocation hasn't been implemented yet");
  return RMW_RET_UNSUPPORTED;
}

rmw_ret_t
rmw_fini_publisher_allocation(rmw_publisher_allocation_t * allocation)
{
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(allocation, RMW_RET_INVALID_ARGUMENT);

  RMW_SET_ERROR_MSG("rmw_fini_publisher_allocation hasn't been implemented yet");
  return RMW_RET_UNSUPPORTED;
}

rmw_publisher_t *
rmw_create_publisher(
  const rmw_node_t * node,
  const rosidl_message_type_support_t * type_supports,
  const char * topic_name,
  const rmw_qos_profile_t * qos_policies,
  const rmw_publisher_options_t * publisher_options)
{
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(node, NULL);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(type_supports, NULL);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(topic_name, NULL);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(qos_policies, NULL);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(publisher_options, NULL);

  rmw_publisher_t * pub = rmw_publisher_allocate();
  pub_sub_data_t * data = rmw_allocate(sizeof(pub_sub_data_t));

  // Populate data->alloc with allocator specified (all other fields are set during registration)
  data->alloc = (hma_allocator_t *)publisher_options->rmw_specific_publisher_payload;
  if (data->alloc == NULL) {
    // TODO(nightduck): Replace hard coded values when serialization works
    //                  Remove all together when TLSF allocator is done
    data->alloc = create_cpu_ringbuf_allocator(4096, 200);
  }

  size_t len = strlen(topic_name);
  pub->implementation_identifier = rmw_get_implementation_identifier();
  pub->data = data;
  pub->topic_name = rmw_allocate(len);
  pub->options = *publisher_options;
  pub->can_loan_messages = true;

  snprintf(pub->topic_name, len, topic_name);

  hazcat_register_publisher(pub);

  return pub;
}

rmw_ret_t
rmw_destroy_publisher(rmw_node_t * node, rmw_publisher_t * publisher)
{
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(node, RMW_RET_INVALID_ARGUMENT);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(publisher, RMW_RET_INVALID_ARGUMENT);

  // Remove publisher from it's message queue
  rmw_ret_t ret = hazcat_unregister_publisher(publisher);
  if (ret != RMW_RET_OK) {
    return ret;
  }

  // Free all allocated memory associated with publisher
  rmw_free(publisher->topic_name);
  rmw_free(publisher->data);
  rmw_publisher_free(publisher);

  return RMW_RET_OK;
}

rmw_ret_t
rmw_get_gid_for_publisher(const rmw_publisher_t * publisher, rmw_gid_t * gid)
{
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(publisher, RMW_RET_INVALID_ARGUMENT);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(gid, RMW_RET_INVALID_ARGUMENT);

  RMW_SET_ERROR_MSG("rmw_publisher_assert_liveliness hasn't been implemented yet");
  return RMW_RET_UNSUPPORTED;
}

rmw_ret_t
rmw_publisher_assert_liveliness(const rmw_publisher_t * publisher)
{
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(publisher, RMW_RET_INVALID_ARGUMENT);

  RMW_SET_ERROR_MSG("rmw_publisher_assert_liveliness hasn't been implemented yet");
  return RMW_RET_UNSUPPORTED;
}

rmw_ret_t
rmw_publisher_wait_for_all_acked(const rmw_publisher_t * publisher, rmw_time_t wait_timeout)
{
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(publisher, RMW_RET_INVALID_ARGUMENT);
  (void)wait_timeout;

  RMW_SET_ERROR_MSG("rmw_publisher_wait_for_all_acked hasn't been implemented yet");
  return RMW_RET_UNSUPPORTED;
}

rmw_ret_t
rmw_publisher_get_actual_qos(const rmw_publisher_t * publisher, rmw_qos_profile_t * qos)
{
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(publisher, RMW_RET_INVALID_ARGUMENT);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(qos, RMW_RET_INVALID_ARGUMENT);

  RMW_SET_ERROR_MSG("rmw_publisher_get_actual_qos hasn't been implemented yet");
  return RMW_RET_UNSUPPORTED;
}

rmw_ret_t
rmw_publish(
  const rmw_publisher_t * publisher,
  const void * ros_message,
  rmw_publisher_allocation_t * allocation)
{
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(publisher, RMW_RET_INVALID_ARGUMENT);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(ros_message, RMW_RET_INVALID_ARGUMENT);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(allocation, RMW_RET_INVALID_ARGUMENT);

  RMW_SET_ERROR_MSG("rmw_publish hasn't been implemented yet");
  return RMW_RET_UNSUPPORTED;
}

rmw_ret_t
rmw_publish_serialized_message(
  const rmw_publisher_t * publisher,
  const rmw_serialized_message_t * serialized_message,
  rmw_publisher_allocation_t * allocation)
{
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(publisher, RMW_RET_INVALID_ARGUMENT);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(serialized_message, RMW_RET_INVALID_ARGUMENT);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(allocation, RMW_RET_INVALID_ARGUMENT);

  RMW_SET_ERROR_MSG("rmw_publish_serialized_message hasn't been implemented yet");
  return RMW_RET_UNSUPPORTED;
}

rmw_ret_t
rmw_borrow_loaned_message(
  const rmw_publisher_t * publisher,
  const rosidl_message_type_support_t * type_support,
  void ** ros_message)
{
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(publisher, RMW_RET_INVALID_ARGUMENT);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(type_support, RMW_RET_INVALID_ARGUMENT);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(ros_message, RMW_RET_INVALID_ARGUMENT);

  RMW_SET_ERROR_MSG("rmw_borrow_loaned_message hasn't been implemented yet");
  return RMW_RET_UNSUPPORTED;
}

rmw_ret_t
rmw_return_loaned_message_from_publisher(const rmw_publisher_t * publisher, void * loaned_message)
{
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(publisher, RMW_RET_INVALID_ARGUMENT);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(loaned_message, RMW_RET_INVALID_ARGUMENT);

  RMW_SET_ERROR_MSG("rmw_return_loaned_message_from_publisher hasn't been implemented yet");
  return RMW_RET_UNSUPPORTED;
}

rmw_ret_t
rmw_publish_loaned_message(
  const rmw_publisher_t * publisher,
  void * ros_message,
  rmw_publisher_allocation_t * allocation)
{
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(publisher, RMW_RET_INVALID_ARGUMENT);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(ros_message, RMW_RET_INVALID_ARGUMENT);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(allocation, RMW_RET_INVALID_ARGUMENT);

  RMW_SET_ERROR_MSG("rmw_publish_loaned_message hasn't been implemented yet");
  return RMW_RET_UNSUPPORTED;
}

rmw_ret_t rmw_get_publishers_info_by_topic(
  const rmw_node_t * node, rcutils_allocator_t * allocator,
  const char * topic_name, bool no_mangle,
  rmw_topic_endpoint_info_array_t * publishers_info)
{
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(node, RMW_RET_INVALID_ARGUMENT);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(allocator, RMW_RET_INVALID_ARGUMENT);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(topic_name, RMW_RET_INVALID_ARGUMENT);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(publishers_info, RMW_RET_INVALID_ARGUMENT);
  if (node->implementation_identifier != rmw_get_implementation_identifier()) {
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
  }
  int validation_result = RMW_NODE_NAME_VALID;
  rmw_ret_t ret = rmw_validate_node_name(topic_name, &validation_result, NULL);
  if (RMW_RET_OK != ret) {
    return ret;
  }
  if (RMW_NODE_NAME_VALID != validation_result) {
    const char * reason = rmw_node_name_validation_result_string(validation_result);
    RMW_SET_ERROR_MSG_WITH_FORMAT_STRING("node_name argument is invalid: %s", reason);
    return RMW_RET_INVALID_ARGUMENT;
  }
  RCUTILS_CHECK_ALLOCATOR_WITH_MSG(
    allocator, "allocator argument is invalid", return RMW_RET_INVALID_ARGUMENT);
  if (RMW_RET_OK != rmw_topic_endpoint_info_array_check_zero(publishers_info)) {
    return RMW_RET_INVALID_ARGUMENT;
  }
  (void)no_mangle;

  RMW_SET_ERROR_MSG("rmw_get_publishers_info_by_topic hasn't been implemented yet");
  return RMW_RET_UNSUPPORTED;
}

// TODO: Have 1 
// rmw_publisher_options_t
// rmw_get_default_publisher_options(void)
// {
//   rmw_publisher_options_t publisher_options = {
//     .rmw_specific_publisher_payload = NULL,
//   };
//   return publisher_options;
// }
#ifdef __cplusplus
}
#endif
