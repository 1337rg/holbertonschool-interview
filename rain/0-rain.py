#!/usr/bin/python3
"""
Module that calculates how much water will be retained after it rains.
"""


def rain(walls):
    """
    Calculate how many square units of water will be retained after it rains.

    Args:
        walls: A list of non-negative integers representing wall heights

    Returns:
        An integer representing the total amount of rainwater retained
    """
    if not walls or len(walls) < 3:
        return 0

    n = len(walls)
    water = 0

    # For each position, find how much water can be trapped
    for i in range(1, n - 1):
        # Find maximum height of wall on left side
        max_left = max(walls[:i])

        # Find maximum height of wall on right side
        max_right = max(walls[i + 1:])

        # Calculate the water level at current position
        water_level = min(max_left, max_right)

        # Add the trapped water if water_level is higher than current wall
        if water_level > walls[i]:
            water += water_level - walls[i]

    return water
