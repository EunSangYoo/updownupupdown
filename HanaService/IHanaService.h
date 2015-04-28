#ifndef ANDROID_IHANA_SERVICE_H
#define ANDROID_IHANA_SERVICE_H

#include <binder/IInterface.h>
#include <binder/IPermissionController.h>
#include <utils/Vector.h>
#include <utils/String16.h>

namespace android {


	class IHanaService : public IInterface
	{
		public:
			DECLARE_META_INTERFACE(HanaService);

			virtual void hanaTouch(uint32_t, uint32_t) = 0;


			enum {
				HANA_TOUCH = IBinder::FIRST_CALL_TRANSACTION,
			};
	};

	class BnHanaService : public BnInterface<IHanaService>
	{
		public:
			virtual status_t    onTransact( uint32_t code,
					const Parcel& data,
					Parcel* reply,
					uint32_t flags = 0);
	};


}; // namespace android

#endif 

