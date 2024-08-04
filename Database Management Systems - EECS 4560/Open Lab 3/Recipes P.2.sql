
-- “List all recipes that contain a dairy ingredient.” --
USE RecipesExample;
SELECT DISTINCT Recipes.RecipeTitle, Ingredients.IngredientName, Ingredient_Classes.IngredientClassDescription
FROM Recipes
INNER JOIN Recipe_Ingredients ON Recipes.RecipeID = Recipe_Ingredients.RecipeID
INNER JOIN Ingredients ON Recipe_Ingredients.IngredientID = Ingredients.IngredientID
INNER JOIN Ingredient_Classes ON Ingredients.IngredientClassID = Ingredient_Classes.IngredientClassID
WHERE Ingredient_Classes.IngredientClassDescription LIKE '%Dairy%';