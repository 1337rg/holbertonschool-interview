#!/usr/bin/node

/**
 * Script that prints all characters of a Star Wars movie
 * The first positional argument is the Movie ID
 * Displays character names in the same order as the API response
 */

const request = require('request');

// Use process.argv[2] to get movie ID from command line
const movieId = process.argv[2];

if (!movieId) {
  console.error('Please provide a movie ID');
  process.exit(1);
}

const filmUrl = `https://swapi-api.hbtn.io/api/films/${movieId}/`;

// Get the film data to access the characters URLs
request(filmUrl, (error, response, body) => {
  if (error) {
    console.error('Error fetching film data:', error);
    process.exit(1);
  }

  if (response.statusCode !== 200) {
    console.error(`Error: Status code ${response.statusCode}`);
    process.exit(1);
  }

  try {
    const filmData = JSON.parse(body);
    const characterUrls = filmData.characters;

    // Process characters in sequence
    processCharacters(characterUrls, 0);
  } catch (parseError) {
    console.error('Error parsing film data:', parseError);
    process.exit(1);
  }
});

/**
 * Process character URLs recursively to maintain order
 * @param {Array} urls - Array of character URLs
 * @param {Number} index - Current index
 */
function processCharacters (urls, index) {
  // Base case: all characters processed
  if (index >= urls.length) {
    return;
  }

  // Fetch character data
  request(urls[index], (error, response, body) => {
    if (error) {
      console.error('Error fetching character data:', error);
      process.exit(1);
    }

    if (response.statusCode !== 200) {
      console.error(`Error: Status code ${response.statusCode} for character URL ${urls[index]}`);
      process.exit(1);
    }

    try {
      const character = JSON.parse(body);
      console.log(character.name);

      // Process next character
      processCharacters(urls, index + 1);
    } catch (parseError) {
      console.error('Error parsing character data:', parseError);
      process.exit(1);
    }
  });
}
