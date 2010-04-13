{if $LDIFError != FALSE || $type == FALSE}
<p style="margin-top:5px;">
  {t}The LDIF export plugin provides methods to download a complete snapshot of the running LDAP directory as ldif. You may save these files for backup purpose or when initializing a new server.{/t}
</p>
<hr>

<table summary="" style="width:100%;">
<tr>
	<td width="30%">
		<LABEL for="text" >{t}Export single entry{/t}</LABEL>
	</td>
	<td>
		<input id="text" type="text" value="" name="single">
	</td>
	<td>
		<button type='submit' name='sfrmgetsingle'>{t}Export{/t}</button>

	</td>
</tr>
<tr>
	<td width="30%">
		<LABEL for="selfull">{t}Export complete LDIF for{/t}</LABEL>
	</td>
	<td>
		<select id="selfull" name="selfull" size="1" title="{t}Choose the department you want to Export{/t}">
			{html_options options=$deplist selected=0}
		</select>
	</td>
	<td>
		<button type='submit' name='sfrmgetfull'>{t}Export{/t}</button>

	</td>
</tr>
	
{if $govmode eq "true"}
<tr>
	<td width="30%">
		<LABEL for="selivbb">{t}Export IVBB LDIF for{/t}</LABEL>
	</td>
	<td>
		<select id="selivbb" name="selivbb" size="1" title="{t}Choose the department you want to Export{/t}">
			{html_options options=$deplist selected=$depselectivbb}
		</select>
	</td>
	<td>
		<button type='submit' name='sfrmgetivbb'>{t}Export{/t}</button>

	</td>
</tr>
{/if}
</table> 


{else}


<br>
	<h3>{t}Export successful{/t}</h3>
<br>
	<div>
		{image path="images/filesaveas.png"}

		<a href = "plugins/ldapmanager/getldif.php{$para}" title="{t}Click here to save the complete LDAP database to a file{/t} ">{t}Click here to save the LDAP Export {/t}</a>


		<br>
		<br>
	</div>
	<div align="right">
		<button type='submit' name='back'>{msgPool type=backButton}</button>

	</div>
{/if}

<hr>

<input type="hidden" name="ignore">
