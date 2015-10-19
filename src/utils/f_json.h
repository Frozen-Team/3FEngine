#ifndef _3FENGINE_SRC_UTILS_F_JSON_HPP_
#define _3FENGINE_SRC_UTILS_F_JSON_HPP_

#include "rapidjson\document.h"
#include "utils\f_typedefs.hpp"

namespace fengine {

	namespace rj = rapidjson;

	class FJson : public rapidjson::Document
	{
		F_DISABLE_COPY(FJson)
	public:
		FJson() = default;
		~FJson() = default;

		auto operator[](const FString& key) -> decltype(rj::Document()[key.c_str()]);
		
		int LoadFile(const FString& file_name);

		int Save();

		int SaveFile(const FString& file_name);

		int LoadRaw(const FString& raw_json);

		const FString& GetRaw() const;

		const static FString& GetErrorDescription(rapidjson::ParseErrorCode code);

	private:
		int Reload();

	private:
		const static FMap<rj::ParseErrorCode, FString> kErrorCodesDescr;

		FString raw_json_;
		FString file_name_;

	};
}
#endif // _3FENGINE_SRC_UTILS_F_JSON_HPP_