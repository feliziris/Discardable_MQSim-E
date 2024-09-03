#include "NVM_Transaction_Flash_TR.h"


namespace SSD_Components
{
	NVM_Transaction_Flash_TR::NVM_Transaction_Flash_TR(Transaction_Source_Type source, stream_id_type stream_id,
		unsigned int data_size_in_byte, LPA_type lpa, PPA_type ppa, const NVM::FlashMemory::Physical_Page_Address& address, SSD_Components::User_Request* user_io_request, NVM::memory_content_type content,
		NVM_Transaction_Flash_RD* related_read, page_status_type written_sectors_bitmap, data_timestamp_type data_timestamp) :
		NVM_Transaction_Flash(source, Transaction_Type::TRIM, stream_id, data_size_in_byte, lpa, ppa, address, user_io_request),
		Content(content), RelatedRead(related_read), write_sectors_bitmap(written_sectors_bitmap), DataTimeStamp(data_timestamp)
	{
	}

	NVM_Transaction_Flash_TR::NVM_Transaction_Flash_TR(Transaction_Source_Type source, stream_id_type stream_id,
		unsigned int data_size_in_byte, LPA_type lpa, PPA_type ppa, SSD_Components::User_Request* user_io_request, NVM::memory_content_type content,
		NVM_Transaction_Flash_RD* related_read, page_status_type written_sectors_bitmap, data_timestamp_type data_timestamp) :
		NVM_Transaction_Flash(source, Transaction_Type::TRIM, stream_id, data_size_in_byte, lpa, ppa, user_io_request),
		Content(content), RelatedRead(related_read), write_sectors_bitmap(written_sectors_bitmap), DataTimeStamp(data_timestamp)
	{
	}

	NVM_Transaction_Flash_TR::NVM_Transaction_Flash_TR(Transaction_Source_Type source, stream_id_type stream_id,
		unsigned int data_size_in_byte, LPA_type lpa, SSD_Components::User_Request* user_io_request, NVM::memory_content_type content,
		page_status_type written_sectors_bitmap, data_timestamp_type data_timestamp) :
		NVM_Transaction_Flash(source, Transaction_Type::TRIM, stream_id, data_size_in_byte, lpa, NO_PPA, user_io_request),
		Content(content), RelatedRead(NULL), write_sectors_bitmap(written_sectors_bitmap), DataTimeStamp(data_timestamp)
	{
	}
}