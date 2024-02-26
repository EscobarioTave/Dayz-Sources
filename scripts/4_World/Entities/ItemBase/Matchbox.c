class Matchbox extends ItemBase
{
	override void InitItemVariables()
	{
		super.InitItemVariables();
		can_this_be_combined = true;
	}
	
	override bool CanIgniteItem( EntityAI ignite_target = NULL )
	{
		if ( GetQuantity() > 0 && GetWet() < GameConstants.STATE_DAMP )
			return true;
		else
			return false;
	}
	
	override void OnIgnitedTarget( EntityAI ignited_item )
	{
		if ( GetGame().IsServer() )
		{
			AddQuantity( -1 );
		}
	}
	
	override void OnIgnitedTargetFailed( EntityAI target_item )
	{
		if ( GetGame().IsServer() )
		{
			AddQuantity( -1 );
		}
	}
	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionLightItemOnFire);
	}
	
	/*
	override bool IsTargetIgnitionSuccessful( EntityAI item_target = NULL )
	{
	}
	*/
}