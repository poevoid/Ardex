import os
from PIL import Image, ImageDraw

# Constants
CHAR_WIDTH = 5
CHAR_HEIGHT = 8  # Including padding (8 pixels tall)
MAX_WIDTH = 56  # Image width limit (56 pixels)

def load_font_from_png(font_image_path):
    """
    Loads the font template from a PNG image with dimensions 456x8 pixels.
    Each character is 5x8 pixels, including 1 pixel of padding on the top and bottom.
    """
    img = Image.open(font_image_path).convert('1')  # Convert to black and white (1-bit)
    font = {}

    # Validate font image dimensions
    img_width, img_height = img.size
    if img_width != 456 or img_height != 8:
        raise ValueError("Font image must have a width of 456px and height of 8px.")

    # Extract each 5x8 character block
    for i in range(91):  # 91 characters (ASCII 32 to 122)
        char_x = i * CHAR_WIDTH  # The x-offset for the character in the image
        char_image = img.crop((char_x, 0, char_x + CHAR_WIDTH, CHAR_HEIGHT))  # Include padding

        # Convert the character image into a 5x8 pixel array (1 = black, 0 = white)
        char_pixels = []
        for y in range(CHAR_HEIGHT):
            row = 0
            for x in range(CHAR_WIDTH):
                if char_image.getpixel((x, y)) == 0:  # Black pixel
                    row |= (1 << (4 - x))  # Set the corresponding bit to 1
            char_pixels.append(row)
        
        # Store the pixels for the character
        font[chr(32 + i)] = char_pixels

    return font

def wrap_text_to_width(text_line, font, max_width=MAX_WIDTH):
    """
    Wraps the input text to the specified width (in pixels).
    Ensures words are not split across lines.
    """
    words = text_line.split()  # Split the line into words
    lines = []
    current_line = ""
    current_width = 0

    for word in words:
        word_width = len(word) * CHAR_WIDTH
        # Check if the word fits in the current line
        if current_width + word_width <= max_width:
            current_line += (word + " ")
            current_width += word_width + CHAR_WIDTH  # Account for the space after the word
        else:
            # Add the current line and start a new one
            lines.append(current_line.strip())
            current_line = word + " "
            current_width = word_width + CHAR_WIDTH
    
    if current_line:
        lines.append(current_line.strip())  # Add the last line

    return lines

def create_image_from_text(text_line, output_path, font):
    """
    Creates an image from a wrapped line of text using the given font.
    """
    wrapped_lines = wrap_text_to_width(text_line, font)
    img_width = MAX_WIDTH
    img_height = len(wrapped_lines) * CHAR_HEIGHT  # Image height accounts for padded characters

    # Create the image (white background)
    img = Image.new('RGB', (img_width, img_height), (255, 255, 255))  # White background
    draw = ImageDraw.Draw(img)

    y_offset = 0
    for line in wrapped_lines:
        x_offset = 0
        for char in line:
            if char in font:
                # Draw red background for the character
                draw.rectangle(
                    [x_offset, y_offset, x_offset + CHAR_WIDTH - 1, y_offset + CHAR_HEIGHT - 1],
                    fill=(255, 0, 0)  # Red background
                )

                # Draw the character itself in black
                char_pixels = font[char]
                for row_idx in range(CHAR_HEIGHT):
                    row = char_pixels[row_idx]
                    for col_idx in range(CHAR_WIDTH):
                        if (row >> (4 - col_idx)) & 1:  # Check if the pixel is black (1) in the character
                            draw.point((x_offset + col_idx, y_offset + row_idx), fill=(0, 0, 0))  # Black text
            x_offset += CHAR_WIDTH

        y_offset += CHAR_HEIGHT

    img.save(output_path)

def process_text_file(input_file, output_folder, font):
    """
    Processes the input text file, creating an image for each line.
    """
    os.makedirs(output_folder, exist_ok=True)

    with open(input_file, 'r') as file:
        lines = file.readlines()

    for idx, line in enumerate(lines):
        line = line.strip()  # Remove any trailing newlines or spaces
        output_path = os.path.join(output_folder, f"line_{idx + 1}.png")
        create_image_from_text(line, output_path, font)

# Example usage
font_image_path = 'Font_5x8ascii.png'  # Path to your PNG font template (456x8 pixels)
input_text_file = 'pokedex_custom_output.txt'  # Path to your input text file
output_folder = 'output_images'  # Folder to save the images

# Load the font from the PNG file
font = load_font_from_png(font_image_path)

# Process the text file and create images
process_text_file(input_text_file, output_folder, font)
