from recipe_repository import RecipeRepository


def print_recipe(recipe: dict, detailed: bool = False):
    print(f"\n [{recipe['id']}] {recipe['title']}")
    print(f"    Категория: {recipe['category']}")

    if detailed:
        print(f"\n    Ингредиенты:")
        for i, ing in enumerate(recipe['ingredients'], 1):
            print(f"      {i}. {ing}")

        print(f"\n    Приготовление:")
        instructions = recipe['instructions'].split('\n')
        for i, step in enumerate(instructions, 1):
            print(f"      {i}. {step}")

        if recipe.get('cooking_time'):
            print(f"\n   ️ Время: {recipe['cooking_time']} мин.")

    print(f"    Добавлено: {recipe['created_at'][:10]}")


def print_recipes(recipes, title: str = "Рецепты"):
    if not recipes:
        print(f"\n {title} не найдены")
        return

    print(f"\n {title} ({len(recipes)}):")
    print("-" * 50)
    for recipe in recipes:
        print(f"   [{recipe['id']}] {recipe['title']} - {recipe['category']}")


def main():
    print(" МЕНЕДЖЕР РЕЦЕПТОВ (простая версия)")
    print("=" * 50)

    repo = RecipeRepository()

    print("\nВСЕ РЕЦЕПТЫ (get_all):")
    all_recipes = repo.get_all()
    print_recipes(all_recipes, "Все рецепты")

    if all_recipes:
        print("\n Пример рецепта (подробно):")
        print_recipe(all_recipes[0], detailed=True)

    print("\nРЕЦЕПТЫ ПО КАТЕГОРИИ:")
    italian_recipes = repo.get_by_category('Итальянская')
    print_recipes(italian_recipes, "Итальянские рецепты")

    print("\n ДОБАВЛЕНИЕ НОВОГО РЕЦЕПТА:")

    new_recipe = {
        'title': 'Греческий салат',
        'category': 'Салаты',
        'ingredients': ['Помидоры', 'Огурцы', 'Сыр фета', 'Маслины', 'Лук'],
        'instructions': '1. Нарезать овощи кубиками\n2. Добавить сыр и маслины\n3. Заправить оливковым маслом',
        'cooking_time': 15,
        'servings': 4
    }

    new_id = repo.add(new_recipe)
    if new_id:
        print(f"\n Новый рецепт добавлен!")
        new_recipe_data = repo.get_by_id(new_id)
        if new_recipe_data:
            print_recipe(new_recipe_data, detailed=True)

    print("\n УДАЛЕНИЕ РЕЦЕПТА (delete):")

    print(f"\nПытаемся удалить рецепт с ID 2...")
    repo.delete(2)

    print("\n Оставшиеся рецепты:")
    remaining = repo.get_all()
    print_recipes(remaining, "Рецепты после удаления")

    print("\n ДОПОЛНИТЕЛЬНАЯ ИНФОРМАЦИЯ:")
    print(f"    Всего рецептов: {repo.count()}")
    print(f"    Категории: {', '.join(repo.get_categories())}")

    if remaining:
        test_id = remaining[0]['id']
        print(f"\n    Поиск рецепта по ID {test_id}:")
        recipe = repo.get_by_id(test_id)
        if recipe:
            print(f"      Найден: {recipe['title']}")

    print(f"\n   Обновление рецепта ID {test_id if remaining else 1}:")
    if remaining:
        repo.update(test_id, {'cooking_time': 30, 'servings': 2})
        updated = repo.get_by_id(test_id)
        if updated:
            print(f"      Новое время: {updated['cooking_time']} мин., порций: {updated['servings']}")

    print("\n" + "=" * 50)
    print(" Программа завершена")


if __name__ == "__main__":
    main()