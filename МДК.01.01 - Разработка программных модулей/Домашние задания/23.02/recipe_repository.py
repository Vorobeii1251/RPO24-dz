from typing import List, Dict, Optional, Any
from datetime import datetime
import copy


class RecipeRepository:

    def __init__(self):
        self._recipes = []
        self._next_id = 1
        self._init_test_data()

    def _init_test_data(self):
        test_recipes = [
            {
                'title': 'Паста Карбонара',
                'category': 'Итальянская',
                'ingredients': ['Спагетти', 'Яйца', 'Бекон', 'Сыр пармезан'],
                'instructions': '1. Сварить пасту\n2. Обжарить бекон\n3. Смешать с яйцами и сыром',
                'cooking_time': 20
            },
            {
                'title': 'Борщ',
                'category': 'Русская',
                'ingredients': ['Свекла', 'Капуста', 'Картофель', 'Морковь', 'Мясо'],
                'instructions': '1. Сварить бульон\n2. Добавить овощи\n3. Варить до готовности',
                'cooking_time': 60
            },
            {
                'title': 'Омлет',
                'category': 'Завтраки',
                'ingredients': ['Яйца', 'Молоко', 'Соль', 'Масло'],
                'instructions': '1. Взбить яйца с молоком\n2. Пожарить на сковороде',
                'cooking_time': 10
            },
            {
                'title': 'Цезарь',
                'category': 'Салаты',
                'ingredients': ['Курица', 'Салат', 'Помидоры', 'Сухарики', 'Соус'],
                'instructions': '1. Обжарить курицу\n2. Нарезать овощи\n3. Смешать с соусом',
                'cooking_time': 25
            }
        ]

        for recipe in test_recipes:
            self.add(recipe)

    def get_all(self) -> List[Dict[str, Any]]:
        return copy.deepcopy(self._recipes)

    def get_by_category(self, category: str) -> List[Dict[str, Any]]:
        return [
            copy.deepcopy(recipe)
            for recipe in self._recipes
            if recipe['category'].lower() == category.lower()
        ]

    def add(self, recipe_data: Dict[str, Any]) -> Optional[int]:
        required_fields = ['title', 'category', 'ingredients', 'instructions']
        for field in required_fields:
            if field not in recipe_data or not recipe_data[field]:
                print(f"Ошибка: отсутствует обязательное поле '{field}'")
                return None

        new_recipe = {
            'id': self._next_id,
            'title': recipe_data['title'],
            'category': recipe_data['category'],
            'ingredients': recipe_data['ingredients'].copy() if isinstance(recipe_data['ingredients'], list) else
            recipe_data['ingredients'],
            'instructions': recipe_data['instructions'],
            'cooking_time': recipe_data.get('cooking_time'),
            'servings': recipe_data.get('servings'),
            'created_at': datetime.now().isoformat()
        }

        self._recipes.append(new_recipe)
        self._next_id += 1

        print(f" Рецепт '{new_recipe['title']}' добавлен с ID: {new_recipe['id']}")
        return new_recipe['id']

    def delete(self, recipe_id: int) -> bool:
        for i, recipe in enumerate(self._recipes):
            if recipe['id'] == recipe_id:
                deleted_title = recipe['title']
                del self._recipes[i]
                print(f" Рецепт '{deleted_title}' (ID: {recipe_id}) удален")
                return True

        print(f" Рецепт с ID {recipe_id} не найден")
        return False

    def get_by_id(self, recipe_id: int) -> Optional[Dict[str, Any]]:
        for recipe in self._recipes:
            if recipe['id'] == recipe_id:
                return copy.deepcopy(recipe)
        return None

    def update(self, recipe_id: int, update_data: Dict[str, Any]) -> bool:
        for recipe in self._recipes:
            if recipe['id'] == recipe_id:
                for key, value in update_data.items():
                    if key in ['title', 'category', 'ingredients', 'instructions', 'cooking_time', 'servings']:
                        recipe[key] = value

                print(f" Рецепт '{recipe['title']}' (ID: {recipe_id}) обновлен")
                return True

        print(f" Рецепт с ID {recipe_id} не найден")
        return False

    def get_categories(self) -> List[str]:
        categories = set()
        for recipe in self._recipes:
            categories.add(recipe['category'])
        return sorted(list(categories))

    def count(self) -> int:
        return len(self._recipes)