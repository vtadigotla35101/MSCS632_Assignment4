import random

# Configuration
DAYS = ["Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"]
SHIFTS = ["Morning", "Afternoon", "Evening"]
MAX_DAYS_PER_WEEK = 5
MIN_PER_SHIFT = 2
MAX_PER_SHIFT = 3  # Defined to trigger "Conflict" logic

class Employee:
    def __init__(self, name, preferred_shift):
        self.name = name
        self.preferred_shift = preferred_shift  # Simple preference: same shift every day
        self.days_worked_count = 0
        self.schedule = {day: None for day in DAYS}

    def can_work(self, day):
        return self.schedule[day] is None and self.days_worked_count < MAX_DAYS_PER_WEEK

    def assign_shift(self, day, shift):
        self.schedule[day] = shift
        self.days_worked_count += 1

def generate_schedule(employees):
    # Master Schedule Structure: {Day: {Shift: [Employee Names]}}
    weekly_schedule = {day: {shift: [] for shift in SHIFTS} for day in DAYS}

    for day in DAYS:
        print(f"--- Scheduling {day} ---")
        
        # 1. First Pass: Try to assign based on Preferences
        for emp in employees:
            if emp.can_work(day):
                pref = emp.preferred_shift
                current_shift_count = len(weekly_schedule[day][pref])
                
                # Check if preferred shift is full
                if current_shift_count < MAX_PER_SHIFT:
                    weekly_schedule[day][pref].append(emp.name)
                    emp.assign_shift(day, pref)
                else:
                    # CONFLICT RESOLUTION: Preferred is full, find another slot
                    assigned_alternate = False
                    for alt_shift in SHIFTS:
                        if alt_shift != pref and len(weekly_schedule[day][alt_shift]) < MAX_PER_SHIFT:
                            weekly_schedule[day][alt_shift].append(emp.name)
                            emp.assign_shift(day, alt_shift)
                            assigned_alternate = True
                            break # Stop looking for shifts this day

        # 2. Second Pass: Ensure Minimum Staffing (2 per shift)
        for shift in SHIFTS:
            while len(weekly_schedule[day][shift]) < MIN_PER_SHIFT:
                # Find available employees
                candidates = [e for e in employees if e.can_work(day)]
                
                if not candidates:
                    print(f"  WARNING: Not enough staff for {day} {shift}")
                    break
                
                # Randomly assign a candidate
                chosen = random.choice(candidates)
                weekly_schedule[day][shift].append(chosen.name)
                chosen.assign_shift(day, shift)
                print(f"  Gap Fill: Assigned {chosen.name} to {day} {shift}")

    return weekly_schedule

def print_schedule(schedule):
    print("\n====== FINAL WEEKLY SCHEDULE ======")
    for day in DAYS:
        print(f"\n{day}:")
        for shift in SHIFTS:
            workers = ", ".join(schedule[day][shift])
            print(f"  {shift:<10}: {workers}")

# --- Main Application Execution ---
if __name__ == "__main__":
    # Input Simulation (Pre-populating for demonstration)
    staff_list = [
        Employee("Alice", "Morning"),
        Employee("Bob", "Morning"),
        Employee("Charlie", "Afternoon"),
        Employee("David", "Afternoon"),
        Employee("Eve", "Evening"),
        Employee("Frank", "Evening"),
        Employee("Grace", "Morning"),
        Employee("Heidi", "Afternoon")
    ]
    
    # Run Logic
    final_schedule = generate_schedule(staff_list)
    print_schedule(final_schedule)