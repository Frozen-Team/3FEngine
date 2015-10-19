#include "f_json.h"

#include "rapidjson/prettywriter.h"
#include "rapidjson/filewritestream.h"
#include <fstream>

#include "components/f_logger.hpp"

namespace fengine {
	const FMap<rj::ParseErrorCode, FString> FJson::kErrorCodesDescr = {
		{ rj::kParseErrorNone, "No error." },
		{ rj::kParseErrorDocumentEmpty, "The document is empty." },
		{ rj::kParseErrorDocumentRootNotSingular, "The document root must not follow by other values." },
		{ rj::kParseErrorValueInvalid, "Invalid value." },
		{ rj::kParseErrorObjectMissName, "Missing a name for object member." },
		{ rj::kParseErrorObjectMissColon, "Missing a colon after a name of object member." },
		{ rj::kParseErrorObjectMissCommaOrCurlyBracket, "Missing a comma or '},' after an object member." },
		{ rj::kParseErrorArrayMissCommaOrSquareBracket, "Missing a comma or ']' after an array element." },
		{ rj::kParseErrorStringUnicodeEscapeInvalidHex, "Incorrect hex digit after \\u escape in string." },
		{ rj::kParseErrorStringUnicodeSurrogateInvalid, "The surrogate pair in string is invalid." },
		{ rj::kParseErrorStringEscapeInvalid, "Invalid escape character in string." },
		{ rj::kParseErrorStringMissQuotationMark, "Missing a closing quotation mark in string." },
		{ rj::kParseErrorStringInvalidEncoding, "Invalid encoding in string." },
		{ rj::kParseErrorNumberTooBig, "Number too big to be stored in double." },
		{ rj::kParseErrorNumberMissFraction, "Miss fraction part in number." },
		{ rj::kParseErrorNumberMissExponent, "Miss exponent in number." },
		{ rj::kParseErrorTermination, "Parsing was terminated." },
		{ rj::kParseErrorUnspecificSyntaxError, "Unspecific syntax error." }
	};

	auto FJson::operator[](const FString& key) -> decltype(rj::Document()[key.c_str()])
	{
		return (*static_cast<rj::Document*>(this))[key.c_str()];
	}

	int FJson::LoadFile(const FString& file_name)
	{
		this->file_name_.assign(file_name);
		return Reload();
	}

	int FJson::Reload()
	{
		std::ifstream in_file;
		in_file.open(this->file_name_.c_str(), std::ifstream::in);
		if (!in_file.is_open())
		{
			LOG(ERROR) << "Error opening json file: " << this->file_name_;
			return -1;
		}

		in_file.seekg(in_file.end);
		auto length = in_file.tellg();
		in_file.seekg(in_file.beg);

		this->raw_json_.clear();
		this->raw_json_.reserve(length);

		this->raw_json_.assign((std::istreambuf_iterator<char>(in_file)), std::istreambuf_iterator<char>());
		in_file.close();

		if (Parse(this->raw_json_.c_str()).HasParseError())
		{
			LOG(ERROR) << "Error while parsing json: " << FJson::GetErrorDescription(GetParseError());
			return -1;
		}

		return 0;
	}

	int FJson::Save()
	{
		std::ofstream out_file;
		out_file.open(this->file_name_.c_str(), std::ofstream::out | std::ofstream::trunc);
		if (!out_file.is_open())
		{
			return -1;
		}
		rj::StringBuffer sb;
		rj::PrettyWriter<rj::StringBuffer> writer(sb);
		Accept(writer);
		// TODO: Error handling
		//auto err = GetParseError();
		//if (err != rj::kParseErrorNone)
		//{
		//	LOG(ERROR) << "Error while writing json: " << err;
		//	return -1;
		//}

		auto& a = *((rj::Document*)this);
		out_file.write(sb.GetString(), sb.GetSize());
		out_file.close();

		return 0;
	}

	int FJson::SaveFile(const FString& file_name)
	{
		this->file_name_ = file_name;
		return this->Save();
	}

	int FJson::LoadRaw(const FString & raw_json)
	{
		this->raw_json_.assign(raw_json);
		Parse(this->raw_json_.c_str());

		return 0;
	}
	const FString & FJson::GetRaw() const
	{
		return this->raw_json_;
	}
	const FString & FJson::GetErrorDescription(rj::ParseErrorCode code)
	{
		return FJson::kErrorCodesDescr.at(code);
	}
}
