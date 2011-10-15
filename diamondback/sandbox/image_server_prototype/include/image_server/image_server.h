/*******************************************************************************
 *
 *      image_server
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
 *      * Neither the name of "image_server-RelWithDebInfo@image_server" nor the names of its
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

#ifndef IMAGE_SERVER_H_
#define IMAGE_SERVER_H_

#include <base_libs/image_proc_policy.h>
#include <base_libs/reconfigure_policy.h>
#include <base_libs/node.h>
#include <base_libs/image_loader.h>
#include <image_server_prototype/ImageServerConfig.h>

typedef image_server_prototype::ImageServerConfig _ImageServerConfig;
typedef base_libs::ReconfigurePolicy< _ImageServerConfig > _ImageServerConfigPolicy;

BASE_LIBS_DECLARE_NODE( ImageServer, base_libs::ImageProcPolicy, _ImageServerConfigPolicy )

BASE_LIBS_DECLARE_NODE_CLASS( ImageServer )
{
private:
	ImageLoader image_loader_;

public:
	bool last_next_image_state_;
	bool last_prev_image_state_;
	unsigned int current_frame_;
	unsigned int direction_;

	ImageServerNode( ros::NodeHandle & nh )
	:
		_ImageServerNodeAdapterType( nh ),
		image_loader_( nh ),
		last_next_image_state_( false ),
		last_prev_image_state_( false ),
		current_frame_( 0 ),
		direction_( 0 )
	{
		
	}

	void spinFirst()
	{
		initAll();
		_ImageServerConfigPolicy::registerCallback( base_libs::auto_bind( &ImageServerNode::reconfigureCB, this ) );
	}

	void spinOnce()
	{
		if ( image_loader_.images_loaded_ )
		{
			if ( current_frame_ < image_loader_.image_cache_.size() )
			{
				ROS_INFO( "Publishing image %d", current_frame_ );
				
				publishImage( image_loader_.image_cache_[current_frame_], "output_image" );
				
				//publishCvImage( image_loader_.image_cache_[current_frame_] );
				if ( config_.auto_advance )
				{
					switch ( direction_ )
					{
					case 0:
						nextFrame();
						break;
					case 1:
						prevFrame();
						break;
					}
				}
			}
		}
		else
		{
			image_loader_.loadImages();
		}
	}

	void nextFrame()
	{
		if ( current_frame_ < image_loader_.image_cache_.size() - 1 )
		{
			++current_frame_;
		}
		else if ( config_.loop )
		{
			current_frame_ = 0;
		}
	}

	void prevFrame()
	{
		if ( current_frame_ > 0 && image_loader_.image_cache_.size() > 0 )
		{
			--current_frame_;
		}
		else if ( config_.loop )
		{
			current_frame_ = image_loader_.image_cache_.size() - 1;
		}
	}

	void reconfigureCB( _ImageServerConfigPolicy::_ReconfigureType &config,
	                    uint32_t level )
	{
		if ( config.auto_advance )
		{
			if ( config.next_image && !config.prev_image ) direction_ = 0;
			else if ( !config.next_image && config.prev_image ) direction_ = 1;
			else direction_ = 0;

			return;
		}

		if ( last_next_image_state_ != config.next_image )
		{
			nextFrame();
		}
		else if ( last_prev_image_state_ != config.prev_image )
		{
			prevFrame();
		}

		last_next_image_state_ = config.next_image;
		last_prev_image_state_ = config.prev_image;
	}
};

#endif /* IMAGE_SERVER_H_ */