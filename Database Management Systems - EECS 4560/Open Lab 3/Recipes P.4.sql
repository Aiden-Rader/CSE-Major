
-- “Show me the recipes that have beef and garlic.” --USE RecipesExample;
SELECT DISTINCT 
    Recipes.RecipeTitle, 
    Beef.IngredientName AS BeefIngredient, 
    Garlic.IngredientName AS GarlicIngredient, 
    Recipe_Classes.RecipeClassDescription
FROM Recipes
INNER JOIN Recipe_Ingredients AS BeefIngredients ON Recipes.RecipeID = BeefIngredients.RecipeID 
AND BeefIngredients.IngredientID = (SELECT IngredientID FROM Ingredients WHERE IngredientName = 'Beef')

INNER JOIN Recipe_Ingredients AS GarlicIngredients ON Recipes.RecipeID = GarlicIngredients.RecipeID 
AND GarlicIngredients.IngredientID = (SELECT IngredientID FROM Ingredients WHERE IngredientName = 'Garlic')

INNER JOIN Ingredients AS Beef ON BeefIngredients.IngredientID = Beef.IngredientID
INNER JOIN Ingredients AS Garlic ON GarlicIngredients.IngredientID = Garlic.IngredientID
INNER JOIN Recipe_Classes ON Recipes.RecipeClassID = Recipe_Classes.RecipeClassID;