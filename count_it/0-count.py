#!/usr/bin/python3
"""
0-count.py
Recursive function that queries the Reddit API, parses the title of all hot
articles, and prints a sorted count of given keywords (case-insensitive).
"""

import requests


def count_words(subreddit, word_list):
    """
    Queries the Reddit API recursively, parses hot article titles,
    and prints a sorted count of keywords (case-insensitive).
    """
    # Normalize word_list: lowercase, count duplicates
    word_weight = {}
    for word in word_list:
        word_lower = word.lower()
        word_weight[word_lower] = word_weight.get(word_lower, 0) + 1

    # Dictionary to store raw counts (how many time each word appear in titles)
    raw_count = {}

    # Helper function to recursively fetch and process hot posts
    def fetch_hot_posts(subreddit, after=None):
        # Build URL for hot posts
        url = f"https://www.reddit.com/r/{subreddit}/hot.json"
        headers = {"User-Agent": "holberton school project"}
        params = {"limit": 100}
        if after:
            params["after"] = after

        try:
            response = requests.get(
                url, headers=headers, params=params, allow_redirects=False
            )
            if response.status_code != 200:
                return  # Invalid subreddit or error

            data = response.json()
            posts = data["data"]["children"]

            # Process each post title
            for post in posts:
                title = post["data"]["title"].lower()
                # Split title into word (only alphanumeric, ignore punctuation)
                words_in_title = []
                current_word = ""
                for char in title:
                    if char.isalnum():
                        current_word += char
                    else:
                        if current_word:
                            words_in_title.append(current_word)
                            current_word = ""
                if current_word:
                    words_in_title.append(current_word)

                # Count occurrences of each keyword in this title
                for word in words_in_title:
                    if word in word_weight:
                        raw_count[word] = raw_count.get(word, 0) + 1

            # Check if there is a next page
            after = data["data"]["after"]
            if after:
                fetch_hot_posts(subreddit, after)  # Recursive call

        except Exception:
            return  # Any error (network, JSON, etc.) → do nothing

    # Start the recursive fetching
    fetch_hot_posts(subreddit)

    # If no matches, print nothing
    if not raw_count:
        return

    # Apply weights: if a word appears multiple times in word_list, multiply
    final_count = {}
    for word, base_count in word_weight.items():
        if word in raw_count:
            final_count[word] = raw_count[word] * base_count

    # Sort: by count descending, then by word ascending
    sorted_items = sorted(final_count.items(), key=lambda x: (-x[1], x[0]))

    # Print results
    for word, count in sorted_items:
        print(f"{word}: {count}")
