/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 17:37:54 by tosilva           #+#    #+#             */
/*   Updated: 2022/11/09 23:43:53 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

/**
 * X11 events and masks
 */
# define KEY_PRESS			02
# define KEY_RELEASE		03
# define BUTTON_PRESS		04
# define BUTTON_RELEASE		05
# define MOTION_NOTIFY		06
# define ENTER_NOTIFY		07
# define LEAVE_NOTIFY		08
# define FOCUS_IN			09
# define FOCUS_OUT			10
# define KEY_MAP_NOTIFY		11
# define EXPOSE				12
# define VISIBILITY_NOTIFY	15
# define DESTROY_NOTIFY		17
# define NO_EVENT_MASK				0L
# define KEY_PRESS_MASK				1L
# define KEY_RELEASE_MASK			2L
# define BUTTON_PRESS_MASK			4L
# define BUTTON_RELEASE_MASK		8L
# define ENTER_WINDOW_MASK			16L
# define LEAVE_WINDOW_MASK			32L
# define KEY_MAP_STATE_MASK			16384L
# define EXPOSURE_MASK				32768L
# define VISIBILITY_CHANGE_MASK		65536L
# define STRUCTURE_NOTIFY_MASK		131072L

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
# define MISSING_IDENTIFIERS_BEFORE_MAP	"Missing identifiers before map"
# define IDENTIFIERS_AFTER_MAP			"An identifier cannot be after the map"
# define TEXTURE_ERROR					"Error with one or more textures"
# define INVALID_TEXTURE_DESCRIPTION	"Invalid texture description"
# define INVALID_COLOUR_DESCRIPTION		"Invalid colour description"
# define INVALID_MAP_CHARACTER			"Map has an invalid character"
# define MAP_WALL_INCOMPLETE			"Map wall isn't closed"
# define MISSING_PLAYER					"The player is missing"
# define MORE_THAN_ONE_PLAYER_GIVEN		"Only one player char is allowed"

// # define MAP_WITH_MISSING_CHARACTERS	"Map must have C, E, and P characters"
// # define NULL_MAP_ERROR				"No map information provided"

# define MLX_CONNECTION_ERROR		"Error connecting with MinilibX"
# define MLX_WINDOW_CREATION_ERROR	"Error creating a new window with MinilibX"
# define MLX_IMAGE_CREATION_ERROR	"Error creating a new image with MinilibX"
# define NULL_MLX_CONNECTION_ERROR	"No mlx connection provided"

/**
 * Cub3D Constants
 */
# define GAME_TITLE	"WIP"

# define MAPWIDTH 24
# define MAPHEIGHT 24
# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480
# define TEXWIDTH 64
# define TEXHEIGHT 64

# define MAP_FLOOR	'0'
# define MAP_WALL	'1'
# define MAP_NORTH	'N'
# define MAP_SOUTH	'S'
# define MAP_WEST	'W'
# define MAP_EAST	'E'

// movement consts
//the constant value is in squares/second
# define MOVESPEED 0.025
//the constant value is in radians/second
# define ROTSPEED 0.01

# define UPDOWNROTSPEED 10

#endif
