package addressbook;

public class Contact {
 private String lastName;
 private String firstName;
 private String phoneNumber;
 private String email;
 public Contact prev = null;
 public Contact next = null;

 public Contact(String lastName, String firstName, String phoneNumber, String email) {
	super();
	this.lastName = lastName;
	this.firstName = firstName;
	this.phoneNumber = phoneNumber;
	this.email = email;
}
public String getLastName() {
	 return lastName;
 }
 public void setLastName(String lastName) {
	 this.lastName = lastName;
 }
 public String getFirstName() {
	 return firstName;
 }
 public void setFirstName(String firstName) {
	 this.firstName = firstName;
 }
 public String getPhoneNumber() {
	 return phoneNumber;
 }
 public void setPhoneNumber(String phoneNumber) {
	 this.phoneNumber = phoneNumber;
 }
 public String getEmail() {
	 return email;
 }
 public void setEmail(String email) {
	 this.email = email;
 }
}
