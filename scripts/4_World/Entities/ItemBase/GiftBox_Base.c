class GiftBox_Base extends Container_Base
{
	protected vector m_HalfExtents; // The Y value contains a heightoffset and not the halfextent !!!
	protected ref OpenableBehaviour m_Openable;
	
	void GiftBox_Base()
	{
		m_HalfExtents 	= vector.Zero;
		m_Openable 		= new OpenableBehaviour(false);

		RegisterNetSyncVariableBool("m_Openable.m_IsOpened");
	}
	
	override bool CanReceiveItemIntoCargo(EntityAI item)
	{
		if (!super.CanReceiveItemIntoCargo(item))
			return false;
		
		if (GameInventory.GetInventoryCheckContext() == InventoryCheckContext.DEFAULT)
		{
			if (!GetGame().IsDedicatedServer())
				return IsOpen();
		}
		
		return true;
	}
	
	
	override void Open()
	{
		m_Openable.Open();
		SetSynchDirty();
	}
	
	override void Close()
	{
		m_Openable.Close();
		SetSynchDirty();
	}
	
	override bool IsOpen()
	{
		return m_Openable.IsOpened();
	}
	
	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionUnpackGift);
	}
	
	override void OnDebugSpawn()
	{
		EntityAI entity;
		if (Class.CastTo(entity, this))
		{
			entity.GetInventory().CreateInInventory("Chemlight_Green");
		}
	}

	override void EEHealthLevelChanged(int oldLevel, int newLevel, string zone)
	{
		super.EEHealthLevelChanged(oldLevel,newLevel,zone);
		
		if (newLevel == GameConstants.STATE_RUINED && GetGame().IsServer())
		{
			MiscGameplayFunctions.DropAllItemsInInventoryInBounds(this, m_HalfExtents);
			DeleteSafe();
		}
	}
}

class GiftBox_Small extends GiftBox_Base {}
class GiftBox_Medium extends GiftBox_Base {}
class GiftBox_Large extends GiftBox_Base {}
