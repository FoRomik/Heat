# -*- coding: utf-8 -*-
import sys
import click
from heat import __version__


def print_version(ctx, param, value):
    """This function prints the version and exits the program in the callback.

        :param click.context ctx: Click internal object that holds state
                                  relevant for the script execution.
        :param click.core.option param: The option.
        :param bool value: Close the programm without printing the version if
                           False.
    """
    if not value or ctx.resilient_parsing:
        return
    click.echo('heat %s (Python %s)' % (
        __version__,
        sys.version[:3]
    ))
    ctx.exit()


@click.command()
@click.option('-f', '--filename', default="init.txt",
              help="Set the name of the init file.")
@click.option(
    '-v', '--version',
    is_flag=True, help='Show version information and exit.',
    callback=print_version, expose_value=False, is_eager=True,
)
def main(filename):
    """Entry point to the program.

        :param str filename: The init filename.
    """
    print("The init file name is:", filename)
