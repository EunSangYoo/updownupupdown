
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
		public:
			BpHanaService(const sp<IBinder>& impl)
				: BpInterface<IHanaService>(impl)
			{
			}

			void hanaTouch(uint32_t x, uint32_t y){
				// printf("x: %u , y : %u\n");
				Parcel data, reply;
				data.writeInt32(x);
				data.writeInt32(y);
				remote()->transact(HANA_TOUCH, data, &reply);
			}
	};

	status_t BnHanaService::onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
	{
		uint32_t temp;
		switch (code) {
			case HANA_TOUCH:
				hanaTouch(data.readInt32(),data.readInt32());
				break;
			default:
				break;
		}
		return 0;
	}


	IMPLEMENT_META_INTERFACE(HanaService, "com.lge.HanaService");

}; // namespace android
