#ifndef UserResponse_h
#define UserResponse_h

namespace user_response {

enum UserResponseType {
	NotSet,
	UserEnteredNavigation,
	UserEnteredData,
	UserClearedData,
	UserSavedData,
	UserViewedVideo,
	UserViewedImage,
	UserListenedToAudio,
};

}

#endif /* UserResponse_h */
