import requests
import time
import re

def sanitize_text(text):
    """
    Removes unwanted characters like newlines and extra spaces from the text.
    """
    return re.sub(r"[\n\f]+", " ", text).strip()

def get_pokedex_entries(limit=251, version='crystal', output_file="pokedex_custom_output.txt"):
    base_url = "https://pokeapi.co/api/v2/pokemon-species"
    pokemon_base_url = "https://pokeapi.co/api/v2/pokemon"
    response = requests.get(f"{base_url}?limit={limit}")
    
    if response.status_code != 200:
        print("Failed to fetch Pokémon species list.")
        return
    
    species_list = response.json().get("results", [])

    with open(output_file, "w") as file:
        for species in species_list:
            species_name = species["name"]
            species_url = species["url"]

            # Fetch species data
            species_response = requests.get(species_url)
            if species_response.status_code != 200:
                print(f"Failed to fetch data for {species_name}.")
                continue

            species_data = species_response.json()
            entries = species_data.get("flavor_text_entries", [])
            
            # Filter for English entries and the specific version
            version_entries = [
                sanitize_text(entry["flavor_text"])
                for entry in entries
                if entry["language"]["name"] == "en" and entry["version"]["name"] == version
            ]
            flavor_text = version_entries[0] if version_entries else "No flavor text available."

            # Fetch Pokémon data for types
            pokemon_response = requests.get(f"{pokemon_base_url}/{species_name}")
            if pokemon_response.status_code != 200:
                print(f"Failed to fetch Pokémon data for {species_name}.")
                continue

            pokemon_data = pokemon_response.json()
            types = [type_info["type"]["name"] for type_info in pokemon_data.get("types", [])]

            # Format the output line
            output_line = f"{species_name.capitalize()} ({', '.join(types)}): {flavor_text}\n"

            # Write to the file
            file.write(output_line)

            # To prevent overwhelming the API, include a slight delay.
            time.sleep(0.1)

    print(f"Customized Pokédex entries saved to {output_file}")

# Fetch all entries for the "crystal" version and save to a file.
get_pokedex_entries(version='crystal')
