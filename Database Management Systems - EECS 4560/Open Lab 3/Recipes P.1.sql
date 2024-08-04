
-- “List all the recipes for salads.” --
USE RecipesExample;
SELECT Recipes.RecipeTitle, Recipe_Classes.RecipeClassDescription
FROM Recipes
INNER JOIN Recipe_Classes ON Recipes.RecipeClassID = Recipe_Classes.RecipeClassID
WHERE Recipe_Classes.RecipeClassDescription LIKE '%Salad%';
