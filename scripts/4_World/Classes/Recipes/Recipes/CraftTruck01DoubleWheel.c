class CraftTruck01DoubleWheel extends RecipeBase
{
	override void Init()
	{
		m_Name = "#STR_CraftTruck01DoubleWheel0";
		m_IsInstaRecipe = false;//should this recipe be performed instantly without animation
		m_AnimationLength = 1;//animation length in relative time units
		m_Specialty = -0.02;// value > 0 for roughness, value < 0 for precision
		
		
		//conditions
		m_MinDamageIngredient[0] = -1;//-1 = disable check
		m_MaxDamageIngredient[0] = 3;//-1 = disable check
		
		m_MinQuantityIngredient[0] = -1;//-1 = disable check
		m_MaxQuantityIngredient[0] = -1;//-1 = disable check
		
		m_MinDamageIngredient[1] = -1;//-1 = disable check
		m_MaxDamageIngredient[1] = 3;//-1 = disable check
		
		m_MinQuantityIngredient[1] = -1;//-1 = disable check
		m_MaxQuantityIngredient[1] = -1;//-1 = disable check
		//----------------------------------------------------------------------------------------------------------------------
		
		//INGREDIENTS
		//ingredient 1
		InsertIngredient(0,"Truck_01_Wheel");//you can insert multiple ingredients this way

		m_IngredientAddHealth[0] = -1;// 0 = do nothing
		m_IngredientSetHealth[0] = -1; // -1 = do nothing
		m_IngredientAddQuantity[0] = 0;// 0 = do nothing
		m_IngredientDestroy[0] = true;//true = destroy, false = do nothing
		m_IngredientUseSoftSkills[0] = false;// set 'true' to allow modification of the values by softskills on this ingredient
		
		//ingredient 2
		InsertIngredient(1,"Truck_01_Wheel");//you can insert multiple ingredients this way
		
		m_IngredientAddHealth[1] = -1;// 0 = do nothing
		m_IngredientSetHealth[1] = -1; // -1 = do nothing
		m_IngredientAddQuantity[1] = 0;// 0 = do nothing
		m_IngredientDestroy[1] = true;// false = do nothing
		m_IngredientUseSoftSkills[1] = false;// set 'true' to allow modification of the values by softskills on this ingredient
		//----------------------------------------------------------------------------------------------------------------------
		
		//result1
		AddResult("Truck_01_WheelDouble");//add results here
		
		m_ResultSetFullQuantity[0] = false;//true = set full quantity, false = do nothing
		m_ResultSetQuantity[0] = -1;//-1 = do nothing
		m_ResultSetHealth[0] = -1;//-1 = do nothing
		m_ResultInheritsHealth[0] = -2;// (value) == -1 means do nothing; a (value) >= 0 means this result will inherit health from ingredient number (value);(value) == -2 means this result will inherit health from all ingredients averaged(result_health = combined_health_of_ingredients / number_of_ingredients)
		m_ResultInheritsColor[0] = -1;// (value) == -1 means do nothing; a (value) >= 0 means this result classname will be a composite of the name provided in AddResult method and config value "color" of ingredient (value)
		m_ResultToInventory[0] = -2;//(value) == -2 spawn result on the ground;(value) == -1 place anywhere in the players inventory, (value) >= 0 means switch position with ingredient number(value)
		m_ResultUseSoftSkills[0] = false;// set 'true' to allow modification of the values by softskills on this result
		m_ResultReplacesIngredient[0] = -1;// value == -1 means do nothing; a value >= 0 means this result will transfer item propertiesvariables, attachments etc.. from an ingredient value
	}

	override bool CanDo(ItemBase ingredients[], PlayerBase player)//final check for recipe's validity
	{
		Truck_01_Wheel ingredient1 = Truck_01_Wheel.Cast(ingredients[0]);
		Truck_01_Wheel ingredient2 = Truck_01_Wheel.Cast(ingredients[1]);
		
		if (!ingredient1 || !ingredient2)
			return false;
		
		if ( !ingredient1.GetHierarchyParent() || ingredient1.GetHierarchyParent() == ingredient1.GetHierarchyRootPlayer() ) 
		{
			if ( !ingredient2.GetHierarchyParent() || ingredient2.GetHierarchyParent() == ingredient2.GetHierarchyRootPlayer() )
				return true;
			else
				return false;
		}
		else
		{
			return false;
		}
	}

	override void Do(ItemBase ingredients[], PlayerBase player,array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		ItemBase ingredient1 = ingredients[0];
		ItemBase ingredient2 = ingredients[1];
		vector ingred_pos;
		
		if(ingredient1.GetHierarchyRootPlayer())
		{
			ingred_pos = ingredient2.GetPosition();
		}
		else
		{
			ingred_pos = ingredient1.GetPosition();
		}
		
		ItemBase result1 = results.Get(0);
		result1.SetPosition(ingred_pos);
	}
};
