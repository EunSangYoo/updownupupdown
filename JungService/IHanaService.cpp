
#define LOG_TAG "HanaService"

#include "IHanaService.h"
#include <utils/Log.h>
#include <binder/IPCThreadState.h>
#include <binder/Parcel.h>
#include <utils/String8.h>
#include <utils/SystemClock.h>
#include <binder/Parcel.h>

#include <private/binder/Static.h>
#include <unistd.h>

namespace android {

	class BpHanaService : public BpInterface<IHanaService>
	{
		
		int ret;

		public:
		BpHanaService(const sp<IBinder>& impl)
			: BpInterface<IHanaService>(impl){}

		int lock_check(void){
			Parcel data, reply;
			remote()->transact(LOCK_CHECK, data, &reply);
			ret = reply.readInt32();
			return ret;
		}

		int touch_check(void){
			Parcel data, reply;
			remote()->transact(TOUCH_CHECK, data, &reply);
			ret = reply.readInt32();
			return ret;
		}

	};

	status_t BnHanaService::onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
	{
		int ret;
		uint32_t temp;
		switch (code) {
			case LOCK_CHECK:

				ret = lock_check();
                reply->writeInt32(ret); 
				printf("server : %x\n",ret);

			break;

			case TOUCH_CHECK :
		
     			ret = touch_check();
                reply->writeInt32(ret); 
				printf("server : %x\n",ret);

		    break;

			default:
				break;
		}
		return 0;
	}

	IMPLEMENT_META_INTERFACE(HanaService, "com.lge.JungService"); 
}; // namespace android
