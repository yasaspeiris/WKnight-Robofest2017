void maze_solve() {
  int numboxes = 0;
  while (1) {
    doaction = nodetravel(SPEED);
    if (doaction == 'L') {
      delay(PADDING);
      linedegreetravel('L', TURNSPEED);
      delay(PADDING);
      path[path_length] = 'L';
      path_togoback[path_length_togoback] = 'L';
    } else if (doaction == 'F') {
      path[path_length] = 'F';
      path_togoback[path_length_togoback] = 'F';
      delay(PADDING);
    } else if (doaction == 'R') {
      delay(PADDING);
      linedegreetravel('R', TURNSPEED);
      delay(PADDING);
      path[path_length] = 'R';
      path_togoback[path_length_togoback] = 'R';
    } else if (doaction == 'B') {
      delay(PADDING);
      linedegreetravel('R', TURNSPEED);
      delay(PADDING);
      path[path_length] = 'B';
      path_togoback[path_length_togoback] = 'B';
      delay(PADDING);
    } else if (doaction == 'C') {
      numboxes++;
      if (numboxes == BOXES) {
        path[path_length] = 'E';
        path_togoback[path_length_togoback] = 'E';
        delay(PADDING);
        SetMasterPower(100); SetSlavePower(100);
        
        setBrakes(255, 255);
        delay(PADDING);
        char col = checkcolor();
        sendcolor(col);
        waitforack();

        reverseline(REVERSESPEED);
        delay(PADDING);

        break;
      } else {
        path[path_length] = 'C';
        path_togoback[path_length_togoback] = 'B';
        delay(PADDING);
        SetMasterPower(60); SetSlavePower(60); front = 0;
        
        setBrakes(255, 255);
        delay(PADDING);
        char col = checkcolor();
        sendcolor(col);
        waitforack();

        reverseline(REVERSESPEED);
        delay(PADDING);
        linedegreetravel('R', TURNSPEED);
        delay(PADDING);
      }


    }
    path_length ++; path_length_togoback++;
    simplify_path(); simplify_path_togoback();

  }
}


void simplify_path()
{
  // only simplify the path if the second-to-last turn was a 'B'
  if (path_length < 3 || path[path_length - 2] != 'B')
    return;

  int total_angle = 0;
  int i;
  for (i = 1; i <= 3; i++)
  {
    switch (path[path_length - i])
    {
      case 'R':
        total_angle += 90;
        break;
      case 'L':
        total_angle += 270;
        break;
      case 'B':
        total_angle += 180;
        break;
    }
  }

  // Get the angle as a number between 0 and 360 degrees.
  total_angle = total_angle % 360;

  // Replace all of those turns with a single one.
  switch (total_angle)
  {
    case 0:
      path[path_length - 3] = 'F';
      break;
    case 90:
      path[path_length - 3] = 'R';
      break;
    case 180:
      path[path_length - 3] = 'B';
      break;
    case 270:
      path[path_length - 3] = 'L';
      break;
  }

  // The path is now two steps shorter.
  path_length -= 2;
}

void simplify_path_togoback()
{

  // only simplify the path if the second-to-last turn was a 'B'
  if (path_length_togoback < 3 || path_togoback[path_length_togoback - 2] != 'B')
    return;

  int total_angle = 0;
  int i;

  for (i = 1; i <= 3; i++)
  {
    switch (path_togoback[path_length_togoback - i])
    {
      case 'R':
        total_angle += 90;
        break;
      case 'L':
        total_angle += 270;
        break;
      case 'B':
        total_angle += 180;
        break;
    }
  }

  // Get the angle as a number between 0 and 360 degrees.
  total_angle = total_angle % 360;

  // Replace all of those turns with a single one.
  switch (total_angle)
  {
    case 0:
      path_togoback[path_length_togoback - 3] = 'F';
      break;
    case 90:
      path_togoback[path_length_togoback - 3] = 'R';
      break;
    case 180:
      path_togoback[path_length_togoback - 3] = 'B';
      break;
    case 270:
      path_togoback[path_length_togoback - 3] = 'L';
      break;
  }

  // The path is now two steps shorter.
  path_length_togoback -= 2;
}



void travelmappedmaze() {

  char tempaction; char b;
  b = nodetravel(SPEED);
  delay(200);
  for (int i = 0 ; i < path_length; i++) {
    tempaction = path[i];


    if (tempaction == 'L') {
      delay(MAPPED_PADDING);
      linedegreetravel('L', TURNSPEED);
      delay(MAPPED_PADDING);
      b = nodetravel(SPEED);
      delay(MAPPED_PADDING);

    } else if (tempaction == 'F') {
      delay(MAPPED_PADDING);
      b = nodetravel(SPEED);
      delay(MAPPED_PADDING);
    } else if (tempaction == 'R') {
      delay(MAPPED_PADDING);
      linedegreetravel('R', TURNSPEED);
      delay(MAPPED_PADDING);
      b = nodetravel(SPEED);
      delay(MAPPED_PADDING);

    } else if (tempaction == 'C') {
      delay(MAPPED_PADDING);
      SetMasterPower(60); SetSlavePower(60); front = 0;
      
      setBrakes(255, 255);
      delay(PADDING);
      char col = checkcolor();
      sendcolor(col);
      waitforack();

      reverseline(REVERSESPEED);
      delay(MAPPED_PADDING);
      linedegreetravel('R', TURNSPEED);
      delay(MAPPED_PADDING);
      char b = nodetravel(SPEED);
      delay(200);
    } else if (tempaction == 'E') {
      delay(MAPPED_PADDING);
      SetMasterPower(60); SetSlavePower(60); front = 0;
      
      setBrakes(255, 255);
      delay(PADDING);
      char col = checkcolor();
      sendcolor(col);
      waitforack();

      reverseline(REVERSESPEED);
      digitalWrite(YELLOWLED, HIGH);
      delay(MAPPED_PADDING);
    }


  }
}

void gotostart() {

  char tempaction; char b;
  linedegreetravel('R', TURNSPEED);//turnback
  delay(200);
  b = nodetravel(SPEED);
  for (int i = path_length_togoback - 1; i >= 0 ; i--) {
    tempaction = path_togoback[i];

    if (tempaction == 'L') {
      delay(RETURN_PADDING);
      linedegreetravel('R', TURNSPEED);
      delay(RETURN_PADDING);
      b = nodetravel(SPEED);
      delay(RETURN_PADDING);

    } else if (tempaction == 'F') {
      delay(RETURN_PADDING);
      b = nodetravel(SPEED);
      delay(RETURN_PADDING);
    } else if (tempaction == 'R') {
      delay(RETURN_PADDING);
      linedegreetravel('L', TURNSPEED);
      delay(RETURN_PADDING);
      b = nodetravel(TURNSPEED);
      delay(RETURN_PADDING);

    }
  }
}
