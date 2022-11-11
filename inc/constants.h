/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 17:37:54 by tosilva           #+#    #+#             */
/*   Updated: 2022/11/11 21:33:47 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

/**
 * Linux keycodes
 */
# define ESC			65307	// ESQ
# define MOVE_UP		119		// W
# define MOVE_DOWN		115		// S
# define MOVE_LEFT		97		// A
# define MOVE_RIGHT		100		// D
# define LOOK_UP		65362	// ↑
# define LOOK_DOWN		65364	// ↓
# define LOOK_LEFT		65361	// ←
# define LOOK_RIGHT		65363	// →
# define TOGGLE_MOUSE	113		// Q

/**
 * Errors - use in ft_strerror
 */
# define NO_FILE_OR_DIRECTORY	2
# define BAD_INPUT				5
# define TOO_MANY_ARGUMENTS		7
# define BAD_FILE_DESCRIPTOR	9
# define NULL_ADDRESS			6
# define ALLOCATION_ERROR		12
# define INVALID_ARGUMENT		22

# define ALLOCATION_FAILED				"Error allocating memory"
# define MORE_THAN_ONE_MAP_GIVEN		"Only a map file is allowed"
# define FILE_NOT_PROVIDED				"File not provider"
# define BAD_FILE_EXTENTION				"File extension must be '.cub'"
# define FILE_OPEN_ERROR				"Error opening file"
# define INVALID_IDENTIFIER				"File has an invalid identifier"
# define MISSING_IDENTIFIERS_BEFORE_MAP	"Missing/invalid identifiers before map"
# define MAP_MUST_BE_LAST				"The map must be the last information"
# define TEXTURE_ERROR					"Error with one or more textures"
# define INVALID_TEXTURE_DESCRIPTION	"Invalid texture description"
# define INVALID_COLOUR_DESCRIPTION		"Invalid colour description"
# define INVALID_MAP_CHARACTER			"Map has an invalid character"
# define MAP_WALL_INCOMPLETE			"Map wall isn't closed"
# define MISSING_PLAYER					"The player is missing"
# define MORE_THAN_ONE_PLAYER_GIVEN		"Only one player char is allowed"
# define NULL_MAP_ERROR					"No map information provided"
# define DUPLICATE_KEYS					"Duplicate keys found"

# define MLX_CONNECTION_ERROR		"Error connecting with MinilibX"
# define MLX_WINDOW_CREATION_ERROR	"Error creating a new window with MinilibX"
# define MLX_IMAGE_CREATION_ERROR	"Error creating a new image with MinilibX"
# define NULL_MLX_CONNECTION_ERROR	"No mlx connection provided"

/**
 * Cub3D Constants
 */
# define GAME_TITLE	"The Guy Game"

# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480

# define MAP_FLOOR	'0'
# define MAP_WALL	'1'
# define MAP_NORTH	'N'
# define MAP_SOUTH	'S'
# define MAP_WEST	'W'
# define MAP_EAST	'E'

// movement consts
//the constant value is in squares/second
# define MOVE_SPEED 0.025
//the constant value is in radians/second
# define ROT_SPEED 0.015

# define UP_DOWN_SPEED 0

#endif
