#!/usr/bin/python3

def canUnlockAll(boxes):
    if not isinstance(boxes, list) or len(boxes) == 0:
        return False

    unlocked = set([0])
    keys = [0]

    while keys:
        current_box = keys.pop()
        for key in boxes[current_box]:
            if key not in unlocked and 0 <= key < len(boxes):
                unlocked.add(key)
                keys.append(key)

    return len(unlocked) == len(boxes)
