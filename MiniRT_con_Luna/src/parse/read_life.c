/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_life.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:34:40 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/30 20:26:06 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

/*
 * check_dup(t_scene *scene, t_type type)
 * --------------------------------------
 * Verifica que los elementos que solo pueden existir una vez
 * en la escena no estén duplicados.
 *
 * Parámetros:
 * - scene: estructura principal de la escena
 * - type: tipo de elemento que se está parseando
 *
 * Cómo funciona:
 * - Si el tipo es CAMERA, comprueba que aún no haya cámara definida.
 * - Si el tipo es AMBIENT, comprueba que aún no haya luz ambiental.
 * - Si el tipo es LIGHT, comprueba que aún no haya luz puntual.
 * - Para el resto de objetos (esferas, planos, cilindros),
 *   siempre devuelve true, ya que pueden repetirse.
 *
 * Relación con el archivo .rt:
 * - Evita configuraciones inválidas como:
 *     C ...   ← primera cámara (válida)
 *     C ...   ← segunda cámara (error)
 *     A ...   ← solo una luz ambiental permitida
 *
 * Devuelve:
 * - true  → el objeto se puede añadir
 * - false → el objeto es un duplicado inválido
 */

 
static bool	check_dup(t_scene *scene, t_type type)
{
	if (type == CAMERA)
		return (!scene->camera.status);
	if (type == AMBIENT)
		return (!scene->ambient.status);
	if (type == LIGHT)
		return (!scene->light.status);
	return (true);
}

/*
 * check_type_syntax(t_type type, int count)
 * -----------------------------------------
 * Verifica que el número de tokens de una línea coincida
 * con lo esperado según el tipo de objeto.
 *
 * Parámetros:
 * - type: tipo de elemento (CAMERA, LIGHT, SPHERE, etc.)
 * - count: número total de tokens en la línea
 *
 * Cómo funciona:
 * - Compara la cantidad de parámetros esperados para cada tipo:
 *     CAMERA   → 4 tokens  (C pos dir fov)
 *     LIGHT    → 3 tokens  (L pos brightness)
 *     AMBIENT  → 3 tokens  (A ratio color)
 *     PLANE    → 4 tokens  (pl pos normal color)
 *     SPHERE   → 4 tokens  (sp pos diameter color)
 *     CYLINDER → 6 tokens  (cy pos axis diameter height color)
 *
 * Relación con el archivo .rt:
 * - Detecta errores de formato como:
 *     "sp 0,0,0 2"            → faltan parámetros
 *     "C 0,0,0 0,0,1 70 42"   → parámetros de más
 *
 * Devuelve:
 * - true  → formato correcto
 * - false → número de parámetros incorrecto
 */

static bool	check_type_syntax(t_type type, int count)
{
	if (type == CAMERA)
		return (count == 4);
	if (type == LIGHT)
		return (count == 3);
	if (type == AMBIENT)
		return (count == 3);
	if (type == PLANE)
		return (count == 4);
	if (type == SPHERE)
		return (count == 4);
	if (type == CYLINDER)
		return (count == 6);
	return (false);
}

/*
 * check_format(t_scene *scene, char **tokens, t_type type, bool *error)
 * ---------------------------------------------------------------------
 * Valida que una línea del archivo .rt tenga un formato correcto
 * antes de parsear sus valores numéricos.
 *
 * Parámetros:
 * - scene: escena actual (para detectar duplicados)
 * - tokens: array de strings generado a partir de la línea
 * - type: tipo de objeto detectado
 * - error: puntero para marcar error global de parseo
 *
 * Cómo funciona:
 * 1. Verifica que el array de tokens no sea NULL.
 * 2. Comprueba que el objeto no esté duplicado si es único
 *    (cámara, luz, ambiente).
 * 3. Cuenta el número de tokens en la línea.
 * 4. Verifica que el número de tokens sea válido según el tipo.
 * 5. Si alguna comprobación falla:
 *    - Muestra un mensaje de error.
 *    - Marca *error = true.
 *    - Devuelve false.
 * 6. Si todo es correcto, devuelve true.
 *
 * Relación con el archivo .rt:
 * - Filtra líneas inválidas antes de convertir strings a números:
 *     "pl 0,0,0 0,1,0 255,0,0"  → OK
 *     "pl 0,0,0 0,1,0"          → Error
 *     "C 0,0,0 0,0,1 70"        → OK
 *     "C 1,1,1 0,0,1 60"        → Error (duplicada)
 *
 * Importante:
 * - Esta función NO parsea valores.
 * - Solo valida estructura y coherencia básica.
 */

bool	check_format(t_scene *scene, char **tokens,
		t_type type, bool *error)
{
	int	i;

	if (!tokens)
	{
		ft_error(F, Z, (char *[]){"Split error", NULL});
		*error = true;
		return (false);
	}
	if (!check_dup(scene, type))
	{
		ft_error(F, Z, (char *[]){"Duplicate unique object", NULL});
		*error = true;
		return (false);
	}
	i = 0;
	while (tokens[i])
		i++;
	if (!check_type_syntax(type, i))
	{
		ft_error(F, Z, (char *[]){"Invalid object parameters", NULL});
		*error = true;
		return (false);
	}
	return (true);
}

// Lee el archivo y parsea la escena
bool	read_file(t_scene *scene, int fd)
{
	bool	has_error;
	t_parse	parse_data;
	char	**tokens;

	has_error = false;
	tokens = read_next_line_tokens(fd);
	while (tokens && !has_error)
	{
		if (tokens[0])
		{
			parse_data = parse_object_type(tokens[0]);
			if (check_format(scene, tokens, parse_data.type, &has_error))
			{
				has_error = assign_values(&parse_data);
				if (!has_error)
					create_scene_object(scene, parse_data);
			}
		}
		free_arg(tokens);
		tokens = read_next_line_tokens(fd);
	}
	free_arg(tokens);
	return (!has_error);
}

/*
Ejemplo de cómo cada línea del archivo .rt se convierte en estructuras internas:

Línea del .rt                 Función                        Estructura llenada
--------------------------------------------------------------------------------
A 0.2 255,255,255             		parse_object_type → AMBIENT         scene.ambient
C 0,0,4 0,0,-1 70             		parse_object_type → CAMERA         	scene.camera
L 1,1,1 0.7                    		parse_object_type → LIGH         	scene.light
cy -1,1,-4 0,-1,0 2 2 255,255,0  	parse_object_type → CYLINDER       	scene.obj[]
sp 1,1,-4 2 255,0,0           		parse_object_type → SPHERE         	scene.obj[]
pl 3,2,-5 1,1,0 0,255,0       		parse_object_type → PLANE         	scene.obj[]
pl -2,-2,-2 0,1,0 0,0,255     		parse_object_type → PLANE         	scene.obj[]

Explicación:
- Cada línea se identifica por su primer token (A, C, L, sp, pl, cy).
- parse_object_type() determina el tipo de objeto/luz/cámara.
- Luego, los valores (posición, color, tamaño, normal, etc.) se convierten en números y se guardan
  en la estructura correspondiente dentro de t_scene.
*/
