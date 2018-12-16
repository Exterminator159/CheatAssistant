#pragma once
template<class ClassName>
class Memory
{
public:
	ClassName instance;
	BOOL readVirtualMemory(ULONG Address, PVOID Response, SIZE_T Size)
	{
		return instance.readVirtualMemory(Address, Response, Size);
	}

	BOOL writeVirtualMemory(ULONG Address, PVOID Value, SIZE_T Size)
	{
		return instance.writeVirtualMemory(Address, Value, Size);
	}
	template<typename T>
	T read(ULONG address){
		T value = T();
		readVirtualMemory(address, &value, sizeof(T));
		return value;
	}
	template<typename T>
	BOOL write(ULONG dwBaseAddress, T Value)
	{
		return writeVirtualMemory(dwBaseAddress, &Value, sizeof(T));
	}

	template <typename T>
	T readOffset(ULONG base_address, std::vector<int> offset)
	{
		DWORD ofset_address = read<DWORD>(base_address);
		T value;
		for (size_t i = 0; i < offset.size(); i++)
		{
			if (ofset_address > 0)
			{
				if ((i + 1) < offset.size())
				{
					ofset_address = read<DWORD>(ofset_address + offset[i]);
				}
				else {
					value = read<T>(ofset_address + offset[i]);
				}
			}
		}
		return value;
	}

	template <typename T>
	bool writeOffset(ULONG base_address, std::vector<int> offset, T value)
	{
		DWORD ofset_address = read<DWORD>(base_address);
		bool result = false;

		for (size_t i = 0; i < offset.size(); i++)
		{
			if (ofset_address)
			{
				if ((i + 1) < offset.size())
				{
					ofset_address = read<DWORD>(ofset_address + offset[i]);
				}
				else {
					result = write<T>(ofset_address + offset[i], value);
				}
			}
		}

		return result;
	}

	std::wstring readWString(ULONG dwBaseAddress, SIZE_T Size)
	{
		wchar_t *buffer = new wchar_t[Size];
		instance.readVirtualMemory(dwBaseAddress, buffer, Size);
		std::wstring wstr(buffer, Size);
		delete[]buffer;
		return wstr;
	}

	std::string readString(ULONG dwBaseAddress, SIZE_T Size)
	{
		char *buffer = new char[Size];
		instance.readVirtualMemory(dwBaseAddress, buffer, Size);
		std::string str(buffer, Size);
		delete[]buffer;
		return str;
	}

	std::vector<byte> readBytes(ULONG dwBaseAddress, SIZE_T Size)
	{
		std::vector<byte> bytes;
		byte * buffer = new byte[Size];
		instance.readVirtualMemory(dwBaseAddress, buffer, Size);
		for (size_t i = 0; i < Size; i++)
		{
			bytes.insert(bytes.end(), buffer[i]);
		}
		delete[]buffer;
		return bytes;
	}

	BOOL writeBytes(ULONG dwBaseAddress, std::vector<byte> Bytes)
	{
		byte * buffer = new byte[Bytes.size()];
		BOOL result = TRUE;
		for (size_t i = 0; i < Bytes.size(); i++)
		{
			buffer[i] = Bytes[i];
		}
		result = instance.writeVirtualMemory(dwBaseAddress, buffer, Bytes.size());
		delete[]buffer;
		return result;
	}
};



