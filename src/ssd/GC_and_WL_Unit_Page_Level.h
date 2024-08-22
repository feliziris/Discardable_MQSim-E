#ifndef GC_AND_WL_UNIT_PAGE_LEVEL_H
#define GC_AND_WL_UNIT_PAGE_LEVEL_H

#include "GC_and_WL_Unit_Base.h"
#include "NVM_PHY_ONFI.h"
#include "../utils/RandomGenerator.h"
#include <queue>


namespace SSD_Components
{
	enum class GCStatus{ IDLE, READ_STATE, WRITE_STATE};

	class GC_and_WL_Unit_Page_Level : public GC_and_WL_Unit_Base
	{
	public:
		GC_and_WL_Unit_Page_Level(const sim_object_id_type& id,
			Address_Mapping_Unit_Base* address_mapping_unit, Flash_Block_Manager_Base* block_manager, TSU_Base* tsu, NVM_PHY_ONFI* flash_controller,
			GC_Block_Selection_Policy_Type block_selection_policy, double gc_threshold, bool preemptible_gc_enabled, double gc_hard_threshold,
			unsigned int channel_count, unsigned int chip_no_per_channel, unsigned int die_no_per_chip, unsigned int plane_no_per_die,
			unsigned int block_no_per_plane, unsigned int page_no_per_block, unsigned int sectors_per_page, 
			bool use_copyback, double rho, unsigned int max_ongoing_gc_reqs_per_plane = 10, 
			bool dynamic_wearleveling_enabled = true, bool static_wearleveling_enabled = true, unsigned int static_wearleveling_threshold = 100, int seed = 432);

		/*This function is used for implementing preemptible GC execution. If for a flash chip the free block
		* pool becomes close to empty, then the GC requests for that flash chip should be prioritized and
		* GC should go on in non-preemptible mode.*/
		bool GC_is_in_urgent_mode(const NVM::FlashMemory::Flash_Chip*);

		void Check_gc_required(const unsigned int free_block_pool_size, const NVM::FlashMemory::Physical_Page_Address& plane_address);
		bool has_valid_subpg(flash_channel_ID_type ChannelID, flash_chip_ID_type ChipID, flash_die_ID_type DieID, flash_plane_ID_type PlaneID, flash_block_ID_type block_id, flash_page_ID_type page_id);
		int count_valid_pages_in_block(const NVM::FlashMemory::Physical_Page_Address& block_address, int page_no_per_block);

	private:
		NVM_PHY_ONFI * flash_controller;
		GCStatus gc_status;

		static const int weighted_moving_average_N = 5;
		int saturation_criteria_count;
		double saturation_criteria_delta;
		double minimum_mode_difference;
			
		double weight[weighted_moving_average_N];
		bool is_saturated;
		bool prev_saturation_status;
		int cumulative_count;
		int WAF_transiaction_period;
		int saturation_start_index;
			
		int get_valid_page_count(flash_block_ID_type block_id);
		int get_valid_subpage_count(flash_block_ID_type block_id);
		int select_victim_block();
		int read_pages();
		int write_pages();	
		bool is_WAF_saturated(double& diff);

		
		std::list<NVM_Transaction*> waiting_submit_transaction; //used for combine transactions (mapping granularity) into big transaction (NAND PAGE granularity)
		
	};
}
#endif // !GC_AND_WL_UNIT_PAGE_LEVEL_H
