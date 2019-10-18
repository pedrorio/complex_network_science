def format_simulation_time(simulation_time):
    if simulation_time <= 60:
        return f'took {simulation_time} seconds'
    elif simulation_time <= 3600:
        return f'took {simulation_time / 60} minutes'
    else:
        return f'took {simulation_time / 3600} hours'
