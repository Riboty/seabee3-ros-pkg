/*******************************************************************************
 *
 *      waypoint_controller
 * 
 *      Copyright (c) 2011, Edward T. Kaszubski ( ekaszubski@gmail.com )
 *      All rights reserved.
 *
 *      Redistribution and use in source and binary forms, with or without
 *      modification, are permitted provided that the following conditions are
 *      met:
 *      
 *      * Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *      * Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following disclaimer
 *        in the documentation and/or other materials provided with the
 *        distribution.
 *      * Neither the name of "waypoint_controller-RelWithDebInfo@waypoint_controller" nor the names of its
 *        contributors may be used to endorse or promote products derived from
 *        this software without specific prior written permission.
 *      
 *      THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *      "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *      LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *      A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *      OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *      SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *      LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *      DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *      THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *      OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *******************************************************************************/

#ifndef WAYPOINT_CONTROLLER_H_
#define WAYPOINT_CONTROLLER_H_

#include <base_node/base_node.h>
#include <common_utils/tf.h>
#include <waypoint_controller/SetBehavior.h>

typedef BaseNode<> _BaseNode;
typedef waypoint_controller::SetBehavior _SetBehavior;

class WaypointController : public _BaseNode
{
public:
	ros::ServiceServer set_behavior_svr_;

	WaypointController( ros::NodeHandle & nh ) : _BaseNode( nh )
	{
		set_behavior_svr_ = nh_local_.advertiseService( "set_behavior", &WaypointController::setBehaviorCB, this );
	}

	bool setBehaviorCB( _SetBehavior::Request & req, _SetBehavior::Response & resp )
	{
		return false;
	}

};


#endif /* WAYPOINT_CONTROLLER_H_ */
